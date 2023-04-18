touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/gonzalo/Escritorio/ProyectosNetbeans/MP-2223/myLanguage1/dist/Debug/GNU-Linux/mylanguage1  < data/SimpleTextbigrams.txt 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
