# Assignment 2

## New Feature 1:

* The sprite moves up and down. 
* In the editor, you can edit the "track height" and "speed". 
* The track height is how far down the sprite will go before switching to going back up to its initial y value, at which point it will switch back to moving down. 
* The speed is how quickly the sprite moves up and down.

## New Feature 2:

* The sprite 'breathes fire'. 
* This means that while the sprite is in the center 40 pixels of its track up and down, a collision shape and fire texture appears offset to the left by 60 pixels, so that it appears to 'breathe fire'. 
* In the editor, a developer can edit the radius of the fire as "flame radius". This changes the radius of the collision shape and the scale of the texture accordingly. 

## Signal Emitted: 

* The signal emitted by this node is "diedByFlame".
* When either the collision shape for the fire guy or for the fire he breathes (both of which are defined in the extension) is hit by the collision shape of the player, the signal "diedByFlame" is emitted. 

## Method Triggered by Signal From Existing Node:

* The method 'void FireGuy::_on_signal_emitted()' is triggered when the Player node emits "game_over" or the Enemy node emits "killedByEnemy".
* In this function, the amount of times the player has died is kept track of by iterating "death_num" and the text in the label for Fire Guy is updated based on how many deaths you've had.

## Extra Credit - Animation
* The fire guy is animated in the cpp so that he flickers moves a bit.
* He is an animated sprite 2d with Sprite Frames
* The sprite frames are set, the animation is set, and play is called in the cpp function "FireGuy::FireGuy()"
  
  
  
# This Assignment is Built on Assignment 1
## As a refresher, the README for Assignment 1 is as follows
  
# 2d platformer: The Legend of Autumn
  
## Playable Character
#### Use the arrow keys and space to move
  * Left key to go left 
  * Right key to go right
  * Down key to crouch
  * Up key to jump
  * Space key can also be used to jump

## Win Conditions
  * Get the key
  * Make it to the chest at the end and touch it once you have the key

## Lose Conditions
  * Touching the enemy will kill you, causing game over
  * Falling off the map will kill you, causing game over

## Interactables
  * Power-up: There is a pumpkin in the map, touch it to get a jump boost
  * Key: There is a key in the map, touch it to pick it up so you can open the chest 

## GUI System
  * Out of game menu: There is a main menu screen with basic instructions and a start button
  * HUD: There is a HUD that shows movement instructions when on the first platform, boost notifications,
    a message in the top right denoting whether or not you have the key,
    and a "You win!" message if you win or "You need the key" if you reach the chest without the key

# Extra Credit
#### Animations:
* The player has animations for idle, run, jump, fall, and crouch walk
* The enemy has a walking cycle
* The key spins in place

#### Sound Effects:
* There is music for the Main Menu screen, music for the game, and a death sound

#### NPC:
* There is an enemy who walks back and forth across a platform, if you touch him you die! His name is Winter

