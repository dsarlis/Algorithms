#!/bin/bash

for i in {1..12}
do 
   ./vacation input$i.txt > a.txt
   if diff output$i.txt a.txt
      then echo SAME!
   else
      echo DIFFERENT!
   fi
done
