#commented section
[

#start a loop          |loopCounter/input|count|
+[

#add 1 to count and move to second next cell 
>+                     |previousInput|count+1|0|
[->+<]                 |previousInput|0|newcount|

#store input
,                      |previousInput|input|count|

#end loop if cell is empty (null char)
]

#go to count
>

#move count to null char s place
[-<+>]<

#loop
[
-

#print input
<.

#empty input cell
[-]

#move count to input cell
>[-<+>]

<
#end loop;
]

#end of commented section
]


#one liner string reverse code (36 chars / bytes)
+[>+[->+<],]>[-<+>]<[-<.[-]>[-<+>]<]

The input may need be flushed for this one to work
(ctrl d )
