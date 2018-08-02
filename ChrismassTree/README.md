ABOUT
=====

    The idea was to create a container of somewhat cpecial structure.
    It is of pyramid-like appearance but also provides fractal-like growth

    Basic element of container has acess to it's
    - parent element ( the one above )
    - 2 sybling elements ( actualy a double-linked circle of arbitrary length of sybling elements )
    - a child element ( that can also have a child element and a circle of sybling elements of it's own )

    The container can be used to store (for example) a sequence of application menue's
    Like
        MAIN_MENU
            <-   CHOICE_1  ->
                <-   SUB_CHOICE_1_1   <->   SUB_CHOICE_1_2   <->   SUB_CHOICE_1_3    <->   ...   <->   SUB_CHOICE_1_1
            <-   CHOICE_2  ->
                ...
                    ...   ...   ...
            <-   CHOICE_3  ->
    Or
		Game
			Lvl-1
				Area-11
					Location-111 -- Location-112 -- Location-113
						room-1111		room-1121		room-1131
						room-1112		room-1122		room-1132
						room-1113		room-1123		room-1133
				Area-2
			Lvl-2
				Area-1
	Etc.

    The structure is quite hard to represent graphically becouse of its almost nature
    But the container is fun to move around inside (the xmass.cpp provides possibility of it)
=====
HOW TO
======

	Our MainTest provides ability to fill up such container in runtime
	
	1. Build solution and run it in Debug mode
	2. Use commands like
	```
		show  elem|ring						--  shows current element | ring bound to current elemen
        push  iter|prev|next|down  element  --  push new element (int) into container 
		goto  iter|prev|uber|next|down		--  move current element in direction (if possible)
        pop									--  pops current element (also kills its children)
        quit								--  quit application
	```
	3. Start with pushing in root-element
	```
		push iter ##
	```