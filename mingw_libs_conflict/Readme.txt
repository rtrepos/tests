

L'objectif de ce test est de mettre en avant le problème de conflit de library: 
la même lib 2 fois dans le path, la première ne contenant pas le symbole requis 
pour construire un main. Au lancement l'erreur arrive au dynamic loading, 
avec un symbole manquant.  

Notes : 
- les 2 dll construites (l'une avec et l'autre sans le symbole)  sont des MODULES 
cmake, en effet les SHARED sont accompagnés d'import lib ce qui résout le problème 
du symbole à la compilation
- le main est linké au nom de la lib installée et non à la target (CMake n'autorise 
pas de se linker à un MODULE) : cela nécessite 2 projets cmake 1 pour les dll.
En fait cela necessite 3 projets (2 pour les 2 dll), ils emblerait que l'install 
de deux tragets avec le même name pose soucis (bug cmake ?) 

Usage : 

compile.bat ERR (le path est mis sur la mauvaise lib) | OK (le path est mis sur la bonne lib) | NO (ménage)
installwin\exe\main.exe
