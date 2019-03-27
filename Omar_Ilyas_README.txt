Omar Ilyas - IT 286 - Professor Kehoe - 3/27/19

Mini Birb Adventures README

Controls
	- Arrow Keys/ WASD - Move up, left, down and right respectively
	- Z - Hold Z key to move faster
	- X - Fire a melee shot(close-range, large hitbox, quick)
	- C - Fire a long shot (long-range,small hitbox, slow)
	- V - Fire a spread shot (mid-range,small hitbox, but launches 3 projectiles in an area, moderate speed)
	- B - Fire rapid fire shots (mid-range, medium hitbox, quick)
	
	- O - Save the game state (this cannot be done if the player is dead.
	- P - Load the saved game state	

Deliverables (All completed!)
	- Common
		- User Interface
		- Playable character  
		- Level transition between 2 levels saving player state information 
		- Load/ Save states
		
	- Specific
		- The player has at least 5 different abilities (Dash, ShootNormal, Long, Spread, Rapid Fire)
		- 5 different obstacles (spikes, heat, fire, Gravity area, bullets, )
		- 3 different enemy behaviors (Charge player, Fly at player. Shoot at player)

Deliverable Descriptions | How To Test All Deliverables
	- Common
		- User Interface
			- Up in the top left corner, there are 2 rectangles: the green bar represents the player's health, while the blue bar represents the cooldown for a projectile. If the player takes damage through an obstacle, the green bar will decrease and change from a green color to a red color. If the player launches a projectile, the blue bar will become empty and increase steadily. Once the blue bar is full again, the player will be allowed to launch another projectile.
			- To test:
				- Green bar: Use WASD to fly over to the first set of spikes you see, and position the player character on the spikes to damage them. Take notice of the upper left corner to see what effect it has on the green bar.
				- Blue bar: Hold either the X, C, V, or B key to launch projectiles from the player character. Take notice of the upper left corner to see what effect that has on the blue bar.
				
		- Playable character
			- All controls are listed at the top of the readme! The player can move around the screen, launch projectiles, and take damage from obstacles.
			- To test:
				- Test the controls listed at the top of the readme while running the game! Take note of what happens to the player character when pressing the bottons listed.
				
		- Level transition between 2 levels
			- In level 1, there is a yellow and black door object at the very right side of the level. If the player character touches this door, a new game window will open displaying the second level. Player health is saved during the level transition, and that health value will carry over to the next level.
			- To test:
				- Use WASD to fly over to the yellow and black door. Take note of what happens when the door is touched. Also take notice of the health value in the upper left corner of the screen.
				
		- Load/Save states
			- When saving, the player and enemy positions and variables are stored in a binary file and can be accessed even if the game is restarted. When loading, the player and enemy positions and variables are set to whatever was last saved. If the level saved is different from the current level being played, another game window will load with the correct save level.
			- To test:
				- In any game level, press the O key to save the game. You'll get a notification stating that the game was saved.
				- Move the player using WASD and/or take damage by flying into an obstacle. This is to reduce health and prove that health is tracked when saving.
				- Press the P key to load the last state that was saved. The player and enemies will teleport to the last positions saved, and the player's health will be reset to the value that was saved.
				
	- Specific
		- The player has at least 5 different abilities 
			- The player has 1 movement ability and 4 projectiles that can be fired, each linked to a different key: 
				- Dash (Z) - makes the player move faster when moving with WASD
				- Melee (X) - makes the player shoot a short-range projectile.
				- Long Shot(C) - makes the player shoot a long-range projectile
				- Spread Shot(V) - makes the player shoot 3 projectiles in a cone formation
				- Rapid Fire Shot(B) - Makes the player shoot a rapid series of mid range shots
			- To test:
				- Press and hold each of the keys listed above one at a time. If you're holding Z, make sure to move the character using WASD in order to see the effects. If you're holding X, C, V, or B, take notice of what shoots from the player.
				
		- 5 different obstacles (spikes, heat, fire, Gravity area, bullets)
			- There are 5 different static obstacles in the game world, each with different ways to damage or hinder the player:
				- Spikes - apply knockback to the player and do a small amount of damage once
				- Heat - do a very small amount of damage continuously for as long as the player is within it
				- Fire - do a moderate amount of damage quickly for as long as the player is touching it
				- Gravity area - slow the player's movement for as long as the player is within it
				- Bottomless Pit (Instant Kill block) - immediately kill the player if touched.
				
			- To test:
				- Move the player to these obstacles using WASD into any of the obstacles mentioned. Take note of what happens to either the player health bar or the player character itself.

		- 3 different enemy behaviors (Charge player, Fly at player. Shoot at player)
			- There are 3 enemies in each level, each with a different enemy behavior:
				- Patroller - walks left and right while on the ground at a moderate speed
				- Chaser - navigates towards the player and phases through walls
				- Shooter - shoots a long projectile every 1.2 seconds
			- To test: Start level 1 and look at each of the dark red enemies and their behaviors.
