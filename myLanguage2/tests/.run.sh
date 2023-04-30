touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/gonzalo/Escritorio/ProyectosNetbeans/MP-2223/myLanguage2/dist/Debug/GNU-Linux/mylanguage2  ../Books/BodasdeSangre_FedericoGarciaLorca.bgr ../Books/quijote.bgr ../Books/fortunata.bgr tests/output/spanish2.bgr 1> tests//.out13 2>&1"
eval $CMD
rm tests//.timeout
