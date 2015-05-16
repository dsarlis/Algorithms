#! /bin/bash

for i in {1..12}
do
     echo Running testcase $i
    (time ./boats < lab02/boats/input$i.txt) > a.txt

    if diff a.txt lab02/boats/output$i.txt
       then echo SAME!
    else
       echo DIFFERENT!
    fi
done
