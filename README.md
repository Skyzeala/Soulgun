###This is the README for Soulgun
##A super cool bullethell game were you take your enemies body with your soulgun

#Collaborators
*Aleksander Kaletin
*Christopher Tevren
*Jared Collums
*Kirani Anderson

##ROADMAP, SOULGUN

#Milesones

*Week one

	- Architecture Document
	- Game Engine
		- Player, Enemy & entities - location
			* Objects to represent the player, enemey entites and their location
		- Map & partial display
			* Map system to display part of the map depending on player location
		- Gameloop
			* Construct the main game loop to handle rending of graphics and listen for input,
				i.e. create even handler.

*Week two

	- Player movement and input
		* Enable user to move around map depending on user input
	- Enemy spawning
		* System for spawning a limited number of enemies in proximity to the player entity
	- Projectiles & collision
		* Player and enemies shoot projectiles
		* Players and enemies disappear from map when projectiles collide with them

*Week three

	- Humanoid enemy type 
		* Enemy that can be “possessed” by soulgun
	- Soulgun functionality
		* Alternate firing mode that causes player entity to switch with humanoid enemy
	  * Soulgun projectile only collides with humanoid enemies

*Week four

	- Enemey movement AI
		* Enemies face and toward player or move away if player gets too close
		* Enemies position themselves in a relavtively even distribution

*Week five
	
	- Scoring
		* Points and/or timer
	- Bug hunt
		* Squish, squash
	- Cosmetic features & stretch goals
		* Better sprite graphics, possibly work on soundeffects, enhanced map
