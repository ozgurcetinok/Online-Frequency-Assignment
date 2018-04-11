globals[time droppedcalls]

breed[calls call]

calls-own[starttime finishtime duration]

to setup


  clear-all
  random-seed 50
  ask patches[set pcolor white]
  reset-ticks
  set time 0

end

to Go

  ask calls[
    if  finishtime > totaltime
   [ set finishtime totaltime ]
    ]

if ticks = totaltime
[
  ask turtles with [shape = "circle"]
  [set size 0]
  stop]

    set time ticks

    create-calls ifelse-value (ProbabilityOfCall >= random-float 1) [1] [0][
    set starttime time
    set duration random-poisson durationmean
    set finishtime starttime + duration
    setxy random-xcor random-ycor
    set shape "circle"
    set size 5
    set color black
    ]

ask calls[
  if finishtime = ticks
  [set size 0]
]
  ask calls with [color = black and starttime = ticks]
  [
  if count turtles with[color = black and finishtime > ticks] in-radius 5 >= 2
 [
     if count turtles with[color = brown and finishtime > ticks] in-radius 5 = 0
      [ set color brown ]
     if count turtles with[color = blue and finishtime > ticks] in-radius 5 = 0
      [ set color blue ]
     if count turtles with[color = yellow and finishtime > ticks] in-radius 5 = 0
      [ set color yellow ]
     ]
  ]
ask calls with [color = black and starttime = ticks]
  [
  if count turtles with[color = black and finishtime > ticks] in-radius 5 >= 2
 [
   set shape "x"
   set color red
   set finishtime totaltime
   set size 3
   set droppedcalls droppedcalls + 1]
  ]

ask calls with [color = yellow and starttime = ticks]
  [
  if count turtles with[color = yellow and finishtime > ticks] in-radius 5 >= 2
 [set shape "x"
   set color red
   set finishtime totaltime
   set size 3
   set droppedcalls droppedcalls + 1]
  ]

  ask calls with [color = brown and starttime = ticks]
  [
  if count turtles with[color = brown and finishtime > ticks] in-radius 5 >= 2
 [set shape "x"
   set color red
   set finishtime totaltime
   set size 3
   set droppedcalls droppedcalls + 1]
  ]

  ask calls with [color = blue and starttime = ticks]
  [
  if count turtles with[color = blue and finishtime > ticks] in-radius 5 >= 2
 [set shape "x"
   set color red
   set finishtime totaltime
   set size 3
   set droppedcalls droppedcalls + 1]
  ]



tick

    export-world "492.csv"


end
