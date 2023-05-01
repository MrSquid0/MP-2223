touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/gonzalo/Escritorio/ProyectosNetbeans/MP-2223/myLanguage3/dist/Debug/GNU-Linux/mylanguage3  -t max ../Books/prep_xx.bgr ../Books/prep_en.bgr ../Books/prep_fr.bgr ../Books/prep_sp.bgr ../Books/prep_ge.bgr 1> tests//.out6 2>&1"
eval $CMD
rm tests//.timeout
