-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1. I want to see the crime scene report on that day.
    SELECT description
    FROM crime_scene_reports
    WHERE month = 7 AND day = 28
    AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses
-- who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- 2. I want to know if there's more crime reports in this street that could help me so I ran
    SELECT description
    FROM crime_scene_reports
    WHERE street = 'Humphrey Street';
--| Theft took place at 03:11. Two people witnessed the event.
--| Credit card fraud took place at 08:41. One person witnessed the incident.
--| Expired parking meter took place at 03:17. Two people witnessed the event.
--| Shoplifting took place at 04:45. Two people witnessed the event.
--| Littering took place at 17:49. Two people witnessed the event.

-- 3. I want to know about the witness in interviews table
    SELECT transcript
    FROM interviews
    WHERE month = 7 AND day = 28 AND year = 2023;
--| “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
--| “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
--| “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
--| IMPORTANT1: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--| IMPORTANT2: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--| IMPORTANT3: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
--| Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.

-- 4. My 'IMPORTANT2' notation seems like the next logic step, since I can't check for cameras.
    SELECT id, account_number, transaction_type, amount
    FROM atm_transactions
    WHERE year = 2023 AND month = 7 AND day = 28
    AND atm_location = 'Leggett Street';
-- OUTPUT:
--+-----+----------------+------------------+--------+
--| id  | account_number | transaction_type | amount |
--+-----+----------------+------------------+--------+
--| 246 | 28500762       | withdraw         | 48     |
--| 264 | 28296815       | withdraw         | 20     |
--| 266 | 76054385       | withdraw         | 60     |
--| 267 | 49610011       | withdraw         | 50     |
--| 269 | 16153065       | withdraw         | 80     |
--| 275 | 86363979       | deposit          | 10     |
--| 288 | 25506511       | withdraw         | 20     |
--| 313 | 81061156       | withdraw         | 30     |
--| 336 | 26013199       | withdraw         | 35     |
--+-----+----------------+------------------+--------+

-- 5. Going to check 'IMPORTANT3' now, as step 4 (IMPORTANT2) is done
-- 5.1 First I need the airport name and abbreviation
    SELECT id, full_name, abbreviation
    FROM airports
    WHERE city = 'Fiftyville';
--+----+-----------------------------+--------------+
--| id |          full_name          | abbreviation |
--+----+-----------------------------+--------------+
--| 8  | Fiftyville Regional Airport | CSF          |
--+----+-----------------------------+--------------+
-- 5.2 Check earliest flight from Fiftyville that day
    SELECT id, hour, minute, destination_airport_id
    FROM flights
    WHERE year = 2023 AND month = 7 AND day = 29
    AND origin_airport_id = 8
    ORDER BY hour ASC, minute ASC;
--+----+------+--------+------------------------+
--| id | hour | minute | destination_airport_id |
--+----+------+--------+------------------------+
--| 36 | 8    | 20     | 4                      |
--| 43 | 9    | 30     | 1                      |
--| 23 | 12   | 15     | 11                     |
--| 53 | 15   | 20     | 9                      |
--| 18 | 16   | 0      | 6                      |
--+----+------+--------+------------------------+

-- * = EARLIEST.
-- 5.3 Check passengers (everyone's now a supect)
    SELECT passport_number, seat
    FROM passengers
    WHERE flight_id = 36;
--+-----------------+------+
--| passport_number | seat |
--+-----------------+------+
--| 7214083635      | 2A   |
--| 1695452385      | 3B   |
--| 5773159633      | 4A   |
--| 1540955065      | 5C   |
--| 8294398571      | 6C   |
--| 1988161715      | 6D   |
--| 9878712108      | 7A   |
--| 8496433585      | 7B   |
--+-----------------+------+
-- 6. Check for people's name and phone number
    SELECT name, phone_number, license_plate FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    WHERE flight_id = 36;
--+--------+----------------+---------------+
--|  name  |  phone_number  | license_plate |
--+--------+----------------+---------------+
--| Doris  | (066) 555-9701 | M51FA04       |
--| Sofia  | (130) 555-0289 | G412CB7       |
--| Bruce  | (367) 555-5533 | 94KL13X       |
--| Edward | (328) 555-1152 | 130LD9Z       |
--| Kelsey | (499) 555-9472 | 0NTHK55       |
--| Taylor | (286) 555-6063 | 1106N58       |
--| Kenny  | (826) 555-1652 | 30G67EN       |
--| Luca   | (389) 555-5198 | 4328GD8       |
--+--------+----------------+---------------+

-- 7. Now I can check for IMPORTANT3 notation (phone_calls)
    SELECT caller, receiver
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28
    AND duration < 60;
--+----------------+----------------+
--|     caller     |    receiver    |
--+----------------+----------------+
--| (130) 555-0289 | (996) 555-8899 |
--| (499) 555-9472 | (892) 555-8872 |
--| (367) 555-5533 | (375) 555-8161 |
--| (499) 555-9472 | (717) 555-1342 |
--| (286) 555-6063 | (676) 555-6554 |
--| (770) 555-1861 | (725) 555-3243 |
--| (031) 555-6622 | (910) 555-3251 |
--| (826) 555-1652 | (066) 555-9701 |
--| (338) 555-6650 | (704) 555-2131 |
--+----------------+----------------+
-- Kelsey called Doris
-- Bruce called a person named Robin that it's not in the plane.

--8. Check for cameras since I got license_plates
    SELECT activity, license_plate, minute
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND year = 2023
    AND hour = 10;
--+----------+---------------+--------+
--| activity | license_plate | minute |
--+----------+---------------+--------+
--| entrance | R3G7486       | 8      |
--| entrance | 13FNH73       | 14     |
--| exit     | 5P2BI95       | 16     |*
--| exit     | 94KL13X       | 18     |*
--| exit     | 6P58WS2       | 18     |*
--| exit     | 4328GD8       | 19     |*
--| exit     | G412CB7       | 20     |*
--| exit     | L93JTIZ       | 21     |*
--| exit     | 322W7JE       | 23     |*
--| exit     | 0NTHK55       | 23     |*
--| exit     | 1106N58       | 35     |
--| entrance | NRYN856       | 42     |
--| entrance | WD5M8I6       | 44     |
--| entrance | V47T75I       | 55     |
--+----------+---------------+--------+
-- Bruce exited 10:18
-- Kelsey exited 10:23

-- 9. Check for where did they go:
    SELECT city
    FROM airports
    WHERE id = 4;
--+---------------+
--|     city      |
--+---------------+
--| New York City |
--+---------------+

-- I'm not a native speaker, so I thought they meant both of them took the plane. When I realized 'them' could be neutral for 'him/her', I tried the only last option available that had a car leaving the park
-- Which is Bruce.
-- He called Robin in the time given by the person in 'IMPORTANT3'.






