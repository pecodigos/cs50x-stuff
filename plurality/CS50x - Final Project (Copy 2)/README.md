# Legend of CS50
### Video Demo: [Legend of CS50 - YouTube](https://www.youtube.com/watch?v=RwlyM2zbD_g)
# Description

Legend of CS50 is an **8-bit-like**, **2D** and **turn-based RPG game** made in **LÖVE2D**. Initially, I wanted this game to have multiple stages or levels, but then, after listening to what **Guy White** had to say about a long first-time game I changed my mind on that, and the game got a lot shorter.

The game has only 2 levels, where the first one is where you can walk, jump, interact with a NPC and enter a wooden door.

The game has three characters. The main character is named **Dart** (I got the inspiration from a *PS1* game called ***Legend of Dragoon***). David, which was inspired by **CS50** teacher **David** (who is one of the best teachers I've seen in my life). I tried to make a little *joke* using one of his classic phrases. And the last, but not least, **Duck**, which in this game is an evil character (~~*sorry for that, duck*~~), and the game final-boss.

The main screen design was made purely from my mind. I didn't have any specific game in mind when designing it.

The battle screen design is inspired by the first ***Final Fantasy*** game. Made on a simple black screen with a white GUI. I didn't use any *libraries*, so at first it seemed really scary to make it, but everything worked fine ~~I guess~~.

I got all the sounds on the game from a website called *freesound.org*, which had everything I needed for free. Also, all sprites were made by me, using a website called *Piskel*.

# Explaining game mechanics

### **Dart mechanics**:

***On the main screen***:

- Dart can walk right (using 'right arrow' key) and left (using 'left arrow' key);
- Dart can jump (using 'space' key). He can only jump when he's on the ground;
- Dart can enter the door (using 'up arrow' key). He can only enter the door for a certain distance;
- Dart can't go past left or right border of the screen;
- Dart can, in a certain way, interact with David. He just needs to be close enough.

***On the battle screen***:

The game is turn-based. After you select an action, your turn is automatically passed.
- Dart can attack (using 'x' key when Attack is selected), once per turn, then his turn is passed;
- Dart can defend (using 'x' key when Defense is selected), once per turn, then his turn is passed.

***Dart battle stats***:

- Attack: 75;
- Defense: 20;
- Total HP: 125;
- Current HP: Starting at 125;
- Current DEF: Starting at 20.

### **Duck mechanics**:

- Duck can only attack, once per turn, then his turn is passed.

***Duck battle stats***:

- Attack: 35;
- Defense: 20;
- Total HP: 500;
- Current HP: Starting at 500.

### **Overall damage calculation**:

***When Dart selects Attack***:

- Damage is equal to Dart's attack minus Duck's defense;
- Then, damage is subtracted from Duck's current HP points.

***When Dart selects Defense***:

- Dart current defense is equal to itself plus his Defense stat plus 5 (the plus five at the end is needed for him to gain 10 health points after Duck's attack);
- This way, he'll mitigate all Duck's attack and heal for 10.

***After one of these two is chosen, Duck will attack Dart back. Then, this will happen***:

- 



## Screens:

- ***Main screen***: Where Dart can move, jump, interact with David and enter a door;
- ***Transition screen***: When Dart enters the door, a transition screen appears before he goes to the actual battle. I used this so the transition gets smoother, not just go from one place to another abruptly;
- ***Battle screen***: Where Dart fights Duck. He can use Attack or Defense. Duck can only use attack;
- ***Winner screen***: End game for the player that defeated the Duck;
- ***Loser screen***: End game for the player that was defeated by the Duck.

# Explaining each file

- ***font.ttf*** - Font used for the game;

- ***main.lua*** - Where all code for the game is;

- ***push.lua*** - The library used for the low resolution look.

The game folder (main folder) has 2 folders inside of it, one called ***"sounds"*** and other called ***"sprites"***.

## 'sprites' is the folder that contains every sprite used:

### Dart's sprites:

***-On the main screen***:

- Idle Dart facing right: ***DART1.png***;
- Idle Dart facing left: ***DART1-2.png***;
- Moving Dart facing right: ***DART2.png***;
- Moving Dart facing left: ***DART2-2.png***;

***-On the battle screen***:

- Idle Dart: ***DART3.png***
- Attacking Dart: ***DART4.png***
- Defending Dart: ***DART5.png***
- Hurt Dart: ***DART6.png***

### David's sprites:

- David character: ***DAVID1.png***;
- David's text balloon: ***BALLOON.png***.
### Duck's sprites:

- Idle Duck: ***DUCK1.png***;
- Attacking ***Duck: DUCK2.png**;
- Hurt Duck: ***DUCK3.png***.

### Main screen stage sprites:

- Moon: ***MOON.png***;
- Stars: ***STAR.png***;
- House: ***HOUSE.png***;
- Door: ***DOOR.png***;
- Floor (and tree): ***FLOOR.png***.


## 'sounds' is the folder that contains every sound used:

- Main level music: ***beginsong.wav***;

- Battle level music: ***fightsong.wav***;

- Jump sound: ***jumpsound.wav***;

- Entering the door sound: ***doorsound.wav***;

- Dart's attack sound: ***swordhit.wav***;

- Dart's defense sound: ***swordshield.wav***;

- Duck's attack sound: ***duckhit.wav***;

- Winner screen sound: ***winnersound.wav***;

- Loser screen sound: ***gameover.wav***.



