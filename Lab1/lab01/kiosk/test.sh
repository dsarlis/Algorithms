#! /bin/bash

for i in {1..31}
do
     echo Running testcase $i
    ./kiosk input$i.txt > a.txt

    if diff a.txt output$i.txt
       then echo SAME!
    else
       echo DIFFERENT!
    fi
done
