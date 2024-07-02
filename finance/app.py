import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT symbol, total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])

    # Get current cash
    current_cash_result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    current_cash = current_cash_result[0]["cash"]

    # Loop through this list and call lookup function to get its current price
    for stock in stocks:
        stock_info = lookup(stock["symbol"])
        current_price = stock_info["price"]

        # Handle cases where stock info or current price didnt find any value
        if stock_info == None or current_price == None:
            return apology("Unable to find stock information")

        # Calculate total value of this stock
        total_value = current_price * stock["total_shares"]
        stock["total_value"] = total_value
        stock["current_price"] = current_price

    return render_template("stocklist.html", stocks=stocks, current_cash=current_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Handle the case where empty string in stock symbol
        if not symbol:
            return apology("You need to enter a stock symbol")

        # Look up for stock symbols and check if it's valid
        stock = lookup(symbol)
        if stock == None:
            return apology("Not a valid stock symbol")

        # Input number of shares
        try:
            shares_num = float(request.form.get("shares"))
        except ValueError:
            return apology("Number of shares needs to be a number, duh!")

        # Check if shares_num is a whole number
        if shares_num != int(shares_num):
            return apology("Number of shares needs to be an integer")

        # Handle the case where shares number is less
        if int(shares_num) <= 0:
            return apology("You must enter a positive number")

        try:
            # Get the stock price and check for current currency
            stock_price = stock["price"]
            currency = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        except Exception as f:
            return apology("An error occurred: " + str(f))

        # Check if user have money to buy the share of stocks
        stocks_bought = stock_price * shares_num
        if stocks_bought > currency[0]["cash"]:
            return apology("You don't have enough money")

        # Get current number of shares
        current_shares_result = db.execute(
            "SELECT total_shares FROM transactions WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)

        if len(current_shares_result) > 0:
            current_shares_old = current_shares_result[0]["total_shares"]
        else:
            current_shares_old = 0

        current_shares = current_shares_old + shares_num

        try:
            # Update the current money the user has left after the buy and number of shares
            db.execute("UPDATE users SET cash = cash - :cost WHERE id = :id",
                       cost=stocks_bought, id=session["user_id"])
            db.execute("UPDATE transactions SET total_shares = ? WHERE user_id = ?",
                       current_shares, session["user_id"])

            # Insert into transactions table a new transaction row
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_type, total_shares) VALUES (:user_id, :symbol, :shares, :price, :type, :total_shares)",
                       user_id=session["user_id"], symbol=symbol, shares=shares_num, price=stock_price, type="buy", total_shares=current_shares)

        except Exception as e:
            return apology("An error occurred:" + str(e))

        # Redict the user to home page
        return redirect("/")

    # Get method
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute(
        "SELECT symbol, shares, price, transaction_type, timestamp FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", transactions=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You need to enter a stock symbol")

        stock = lookup(symbol)
        print(stock)

        if stock == None:
            return apology("Invalid stock symbol")

        else:
            return render_template("quoted.html", symbol=stock['symbol'], price=stock['price'])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Transform password into hashes
        hashed_pass = generate_password_hash(password)

        if not username:
            return apology("You forgot your username")

        # Check passwords cases
        if not password:
            return apology("You forgot your password")

        elif not confirmation:
            return apology("You forgot the confirmation")

        elif password != confirmation:
            return apology("Passwords do not match")

        # Check if user is already registered
        result = db.execute("SELECT * FROM users WHERE username = ?", username)
        if result:
            return apology("Username already exists")

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashed_pass)
        username_id = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = username_id[0]['id']
        return redirect(url_for('index'))

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Input for stock symbol
        selected_stock = request.form.get("symbol")

        # Check for empty string
        if not selected_stock:
            return apology("You need to enter a stock symbol")

        # Check if user has the selected stock
        has_stock = db.execute(
            "SELECT * FROM transactions WHERE user_id = ? AND symbol = ?", session["user_id"], selected_stock)

        # Check if its not an empty string
        if not has_stock:
            return apology("You don't have any shares of this stock")

        # Check stock price and handle the case where it returns None
        stock_info = lookup(selected_stock)
        current_price = stock_info["price"]
        if current_price == None:
            return apology("Symbol is not valid")

        # Input for number of shares
        select_share = int(request.form.get("shares"))

        # Check if number of shares is more than 0
        if select_share <= 0:
            return apology("You need to enter a value greater than 0")

        # Get current number of shares
        current_shares_result = db.execute(
            "SELECT total_shares FROM transactions WHERE user_id = ? AND symbol = ?", session["user_id"], selected_stock)
        current_shares_old = current_shares_result[0]["total_shares"]

        # Check if user has that amount of shares
        if current_shares_old == 0:
            return apology("You don't have that number of shares")

        current_shares = current_shares_old - select_share

        if current_shares < 0:
            return apology("You don't have that number of shares")

        db.execute("UPDATE transactions SET total_shares = ? WHERE user_id = ? AND symbol = ?",
                   current_shares, session["user_id"], selected_stock)

        # Get the amount the money made in this transaction
        sell_amount = current_price * select_share

        try:
            # Update the current money user has after selling the stocks
            db.execute("UPDATE users SET cash = cash + :sell WHERE id = :id",
                       sell=sell_amount, id=session["user_id"])

            # Update transactions table
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_type, total_shares) VALUES (:user_id, :symbol, :shares, :price, :type, :total_shares)",
                       user_id=session["user_id"], symbol=selected_stock, shares=select_share, price=current_price, type='sell', total_shares=current_shares)

        except Exception as f:
            return apology("An error occurred: " + str(f))

        # Return user to home page
        return redirect("/")

    else:
        # Query the database for the stocks
        stocks = db.execute("SELECT symbol FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])

        # Pass the stocks to the template
        return render_template("sell.html", stocks=stocks)


@app.route("/changepass", methods=["GET", "POST"])
@login_required
def changepass():

    if request.method == "POST":

        # Inputs for old password, new password and confirmation
        old_pass = request.form.get("oldpass")
        new_pass = request.form.get("newpass")
        confirmation = request.form.get("confirmation")

        # Check for empty string
        if not old_pass or not new_pass or not confirmation:
            return apology("You forgot an empty field")

        # If new password doesn't match with confirmation
        elif new_pass != confirmation:
            return apology("New password doesn't match the confirmation")

        # Check if old password matches the password in database
        check_pass = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])

        if not check_password_hash(check_pass[0]["hash"], old_pass):
            return apology("Wrong old password")

        # Transform new password into hashes
        hashed_newpass = generate_password_hash(new_pass)

        # Update new password in database
        db.execute("UPDATE users SET hash = ? WHERE id = ?", hashed_newpass, session["user_id"])

        # Display sucess message to user and then redirect
        flash("Your password has been successfully updated!")

        return redirect("/")

    else:
        return render_template("changepass.html")
