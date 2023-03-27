touch tests//.timeout
CMD="   /home/gonzalo/Escritorio/ProyectosNetbeans/MP-2223/myLanguage0/dist/Debug/GNU-Linux/mylanguage0  < data/SimpleText.txt 1> tests//.out4 2>&1"
eval $CMD
rm tests//.timeout
