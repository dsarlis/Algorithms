#! /bin/bash

for i in {1..30}
do
     echo Running testcase $i
    (time ./testcases < lab03/testcases/input$i.txt) > a.txt

    if diff a.txt lab03/testcases/output$i.txt
       then echo SAME!
    else
       echo DIFFERENT!
    fi
done
