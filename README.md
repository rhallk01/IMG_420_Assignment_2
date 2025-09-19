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
