

L'objectif de ce test est de mettre en avant le probl�me de conflit de library: 
la m�me lib 2 fois dans le path, la premi�re ne contenant pas le symbole requis 
pour construire un main. Au lancement l'erreur arrive au dynamic loading, 
avec un symbole manquant.  

Notes : 
- les 2 dll construites (l'une avec et l'autre sans le symbole)  sont des MODULES 
cmake, en effet les SHARED sont accompagn�s d'import lib ce qui r�sout le probl�me 
du symbole � la compilation
- le main est link� au nom de la lib install�e et non � la target (CMake n'autorise 
pas de se linker � un MODULE) : cela n�cessite 2 projets cmake 1 pour les dll.
En fait cela necessite 3 projets (2 pour les 2 dll), ils emblerait que l'install 
de deux tragets avec le m�me name pose soucis (bug cmake ?) 

Usage : 

compile.bat ERR (le path est mis sur la mauvaise lib) | OK (le path est mis sur la bonne lib) | NO (m�nage)
installwin\exe\main.exe
