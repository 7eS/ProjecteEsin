###!------------------------------------------------------------------
###! JOC DE PROVES DE LABERINT
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###1 Laberint: Constructora amb dimensions
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###1.1 Entrada correcta
###!------------------------------------------------------------------
###!
#init lab1x1 laberint 1 1
#print
1 1
***
* *
***
##1 1
##***
##* *
##***
#init lab3x3 laberint 3 3
#print
3 3
*******
* * * *
*******
* * * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##*******
##* * * *
##*******
##* * * *
##*******
#init lab5x2 laberint 5 2
#print
5 2
*****
* * *
*****
* * *
*****
* * *
*****
* * *
*****
* * *
*****
##5 2
##*****
##* * *
##*****
##* * *
##*****
##* * *
##*****
##* * *
##*****
##* * *
##*****
#init lab2x5 laberint 2 5
#print
2 5
***********
* * * * * *
***********
* * * * * *
***********
##2 5
##***********
##* * * * * *
##***********
##* * * * * *
##***********
###!
###!------------------------------------------------------------------
###1.2 Entrada incorrecta
###!------------------------------------------------------------------
###!
#init laberr laberint 0 14
Error::laberint:30:El num de fils o cols es incorrecte.
##Error::laberint:30:El num de fils o cols es incorrecte.
#init laberr laberint 12 0
Error::laberint:30:El num de fils o cols es incorrecte.
##Error::laberint:30:El num de fils o cols es incorrecte.
#init laberr laberint 0 0
Error::laberint:30:El num de fils o cols es incorrecte.
##Error::laberint:30:El num de fils o cols es incorrecte.
###!
###!------------------------------------------------------------------
###1.3 Entrada gran
###!------------------------------------------------------------------
###!
#init lab_gran laberint 100 100
#num_files
100
##100
#num_columnes
100
##100
#lab1x1 destroy
#lab3x3 destroy
#lab5x2 destroy
#lab2x5 destroy
#lab_gran destroy 
###!
###!
###!------------------------------------------------------------------
###2 Laberint: Constructora amb fitxers
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###2.1 Laberint sense cicles
###!------------------------------------------------------------------
###!
#init lab_unic laberint ./laberint_3x3.txt
#print
3 3
*******
*   * *
*** * *
* * * *
* * ***
* *   *
*******
##3 3
##*******
##*   * *
##*** * *
##* * * *
##* * ***
##* *   *
##*******
###!
###!------------------------------------------------------------------
###2.2 Laberint amb cicles
###!------------------------------------------------------------------
###!
#init lab_cicle laberint ./laberint_3x3_cicles.txt
#print
3 3
*******
*     *
*** * *
*   * *
* * * *
* *   *
*******
##3 3
##*******
##*     *
##*** * *
##*   * *
##* * * *
##* *   *
##*******
###!
###!------------------------------------------------------------------
###2.3 Laberint sense portes
###!------------------------------------------------------------------
###!
#init lab_sense_portes laberint ./laberint_3x3_senseportes.txt
#print
3 3
*******
* * * *
*******
* * * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##*******
##* * * *
##*******
##* * * *
##*******
###!
###!------------------------------------------------------------------
###2.4 Laberint gran
###!------------------------------------------------------------------
###!
#init lab_gran laberint ./laberint_100x100.txt
#num_files
100
##100
#num_columnes
100
##100
###!
###!
###!------------------------------------------------------------------
###3 Laberint: Constructora per copia, assignacio i destructora
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###3.1 Constructora per copia
###!------------------------------------------------------------------
###!
#initcopy copia = lab_unic
#copia print
3 3
*******
*   * *
*** * *
* * * *
* * ***
* *   *
*******
##3 3
##*******
##*   * *
##*** * *
##* * * *
##* * ***
##* *   *
##*******
#copia destroy
#initcopy copia = lab_cicle
#copia print
3 3
*******
*     *
*** * *
*   * *
* * * *
* *   *
*******
##3 3
##*******
##*     *
##*** * *
##*   * *
##* * * *
##* *   *
##*******
#copia destroy
#initcopy copia = lab_sense_portes
#copia print
3 3
*******
* * * *
*******
* * * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##*******
##* * * *
##*******
##* * * *
##*******
#copia destroy
#initcopy copia = lab_gran
#copia num_files
100
##100
#copia num_columnes
100
##100
#copia destroy
###!
###!------------------------------------------------------------------
###3.2 Copia
###!------------------------------------------------------------------
###!
#init copia laberint 1 1
#copia = lab_unic
#copia print
3 3
*******
*   * *
*** * *
* * * *
* * ***
* *   *
*******
##3 3
##*******
##*   * *
##*** * *
##* * * *
##* * ***
##* *   *
##*******
#copia = lab_cicle
#copia print
3 3
*******
*     *
*** * *
*   * *
* * * *
* *   *
*******
##3 3
##*******
##*     *
##*** * *
##*   * *
##* * * *
##* *   *
##*******
#copia = lab_gran
#copia num_files
100
##100
#copia num_columnes
100
##100
#copia = lab_sense_portes
#copia print
3 3
*******
* * * *
*******
* * * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##*******
##* * * *
##*******
##* * * *
##*******
###!
###!------------------------------------------------------------------
###3.3 Destructora
###!------------------------------------------------------------------
###!
#copia destroy
#lab_unic destroy
#lab_cicle destroy
#lab_sense_portes destroy
#lab_gran destroy
###!
###!
###!------------------------------------------------------------------
###4 Laberint: consultores de files i columnes
###!------------------------------------------------------------------
###!
#init lab1 laberint ./laberint_7x15.txt
#init lab2 laberint ./laberint_12x3.txt
#init lab3 laberint 1 1
#init lab4 laberint 20 2
#init lab5 laberint ./laberint_3x3_senseportes.txt
###!
###!
#lab1 num_columnes 
15
##15
#lab1 num_files
7
##7
#lab2 num_columnes
3
##3
#lab2 num_files
12
##12
#lab3 num_columnes
1
##1
#lab3 num_files
1
##1
#lab4 num_columnes
2
##2
#lab4 num_files
20
##20
#lab5 num_columnes
3
##3
#lab5 num_files
3
##3
###!
###!
###!------------------------------------------------------------------
###5 Laberint: obre_porta
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###5.1 Obertura erronia
###!------------------------------------------------------------------
###!
#lab1 obre_porta_l Norte 2 2
Error::cambra:20:La paret no existeix.
##Error::cambra:20:La paret no existeix.
#lab1 obre_porta_l N 0 0
Error::laberint:31:La posicio no existeix.
##Error::laberint:31:La posicio no existeix.
#lab1 obre_porta_l S 7 16
Error::laberint:31:La posicio no existeix.
##Error::laberint:31:La posicio no existeix.
#lab1 obre_porta_l S 8 15
Error::laberint:31:La posicio no existeix.
##Error::laberint:31:La posicio no existeix.
#lab3 obre_porta_l E 1 2
Error::laberint:31:La posicio no existeix.
##Error::laberint:31:La posicio no existeix.
###!
#lab1 obre_porta_l N 1 1
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
#lab1 obre_porta_l N 1 8
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
#lab1 obre_porta_l S 7 14
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
#lab1 obre_porta_l O 3 1
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
#lab1 obre_porta_l E 2 15
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
###!
#lab3 obre_porta_l N 1 1
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
#lab3 obre_porta_l S 1 1
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
#lab3 obre_porta_l E 1 1
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
#lab3 obre_porta_l O 1 1
Error::laberint:32:No es pot obrir una porta a l'exterior.
##Error::laberint:32:No es pot obrir una porta a l'exterior.
###!
###!------------------------------------------------------------------
###5.2 Obertura correcta
###!------------------------------------------------------------------
###!
###! les seguents operacions es realitzen amb lab5 (3x3)
#sel_curr_obj lab5
#obre_porta_l S 1 1
#print
3 3
*******
* * * *
* *****
* * * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##* *****
##* * * *
##*******
##* * * *
##*******
#obre_porta_l S 1 1
#print
3 3
*******
* * * *
* *****
* * * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##* *****
##* * * *
##*******
##* * * *
##*******
#obre_porta_l N 2 1
#print
3 3
*******
* * * *
* *****
* * * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##* *****
##* * * *
##*******
##* * * *
##*******
#obre_porta_l O 2 2
#print
3 3
*******
* * * *
* *****
*   * *
*******
* * * *
*******
##3 3
##*******
##* * * *
##* *****
##*   * *
##*******
##* * * *
##*******
#obre_porta_l O 3 3
#print
3 3
*******
* * * *
* *****
*   * *
*******
* *   *
*******
##3 3
##*******
##* * * *
##* *****
##*   * *
##*******
##* *   *
##*******
#obre_porta_l E 3 1
#print
3 3
*******
* * * *
* *****
*   * *
*******
*     *
*******
##3 3
##*******
##* * * *
##* *****
##*   * *
##*******
##*     *
##*******
###!
###!
###!------------------------------------------------------------------
###6 Laberint: operator() 
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###6.1 Consultes correctes
###!------------------------------------------------------------------
###!
#obt_cambra 1 1
***
* *
* *
##***
##* *
##* *
#obt_cambra 3 3
***
  *
***
##***
##  *
##***
#obt_cambra 2 1
* *
*  
***
##* *
##*  
##***
#obt_cambra 1 2
***
* *
***
##***
##* *
##***
#obt_cambra 2 2
***
  *
***
##***
##  *
##***
###!
###!------------------------------------------------------------------
###6.2 Consultes incorrectes
###!------------------------------------------------------------------
###!
#lab3 obt_cambra 4 1
Error::laberint:31:La posicio no existeix.
##Error::laberint:31:La posicio no existeix.
#lab5 obt_cambra 0 2
Error::laberint:31:La posicio no existeix.
##Error::laberint:31:La posicio no existeix.
###!
###!
###!------------------------------------------------------------------
###7 Laberint:tanca_porta
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###7.1 Tancaments correctes
###!------------------------------------------------------------------
###!
#sel_curr_obj lab5
#tanca_porta_l N 1 1
#obt_cambra 1 1
***
* *
* *
##***
##* *
##* *
#tanca_porta_l S 1 1
#obt_cambra 1 1
***
* *
***
##***
##* *
##***
#obt_cambra 2 1
***
*  
***
##***
##*  
##***
#tanca_porta_l O 3 3
#print
3 3
*******
* * * *
*******
*   * *
*******
*   * *
*******
##3 3
##*******
##* * * *
##*******
##*   * *
##*******
##*   * *
##*******
#tanca_porta_l E 3 3
#print
3 3
*******
* * * *
*******
*   * *
*******
*   * *
*******
##3 3
##*******
##* * * *
##*******
##*   * *
##*******
##*   * *
##*******
#tanca_porta_l E 2 1
#print
3 3
*******
* * * *
*******
* * * *
*******
*   * *
*******
##3 3
##*******
##* * * *
##*******
##* * * *
##*******
##*   * *
##*******
#tanca_porta_l S 2 2
#print
3 3
*******
* * * *
*******
* * * *
*******
*   * *
*******
##3 3
##*******
##* * * *
##*******
##* * * *
##*******
##*   * *
##*******
#tanca_porta_l S 3 2
#print
3 3
*******
* * * *
*******
* * * *
*******
*   * *
*******
##3 3
##*******
##* * * *
##*******
##* * * *
##*******
##*   * *
##*******
###!
#lab1 destroy
#lab2 destroy
#lab3 destroy
#lab4 destroy
#lab5 destroy
###!
###! Fi del joc de proves de laberint
###! 
