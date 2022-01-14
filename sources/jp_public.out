###!==================================================================
###! JOC DE PROVES PUBLIC
###!==================================================================
###!
###! Memoria general
#set_memory 100000 1000000000
###!
###!
#load jp_public_cambra.in
###!------------------------------------------------------------------
###! JOC DE PROVES DE CAMBRA
###!------------------------------------------------------------------
###!
###!
###!------------------------------------------------------------------
###1 Cambra: Constructora
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###1.1 Constructora basica
###!------------------------------------------------------------------
###!
#init c cambra
#print_c
***
* *
***
##***
##* *
##***
###!
###!------------------------------------------------------------------
###1.2 Constructora 1 orientacio
###!------------------------------------------------------------------
###!
#init cN cambra N
#print_c
* *
* *
***
##* *
##* *
##***
#init cE cambra E
#print_c
***
*  
***
##***
##*  
##***
#init cO cambra O
#print_c
***
  *
***
##***
##  *
##***
#init cS cambra S
#print_c
***
* *
* *
##***
##* *
##* *
###!
###!------------------------------------------------------------------
###1.3 Constructora 2 orientacions
###!------------------------------------------------------------------
###!
#init cNS cambra N S
#print_c
* *
* *
* *
##* *
##* *
##* *
#init cEO cambra E O
#print_c
***
   
***
##***
##   
##***
#init cNE cambra N E
#print_c
* *
*  
***
##* *
##*  
##***
#init cNO cambra N O
#print_c
* *
  *
***
##* *
##  *
##***
#init cES cambra E S
#print_c
***
*  
* *
##***
##*  
##* *
#init cSO cambra S O
#print_c
***
  *
* *
##***
##  *
##* *
###!
###!------------------------------------------------------------------
###1.4 Constructora 3 orientacions
###!------------------------------------------------------------------
###!
#init cNES cambra N E S
#print_c
* *
*  
* *
##* *
##*  
##* *
#init cESO cambra E S O
#print_c
***
   
* *
##***
##   
##* *
#init cSON cambra S O N
#print_c
* *
  *
* *
##* *
##  *
##* *
#init cNEO cambra N E O
#print_c
* *
   
***
##* *
##   
##***
###!
###!------------------------------------------------------------------
###1.5 Constructora 4 orientacions
###!------------------------------------------------------------------
###!
#init cNESO cambra N E O S
#print_c
* *
   
* *
##* *
##   
##* *
###!
###!
###!------------------------------------------------------------------
###2 Cambra: constructora per copia i destructora
###!------------------------------------------------------------------
###!
#initcopy ccopia = c
#ccopia print_c
***
* *
***
##***
##* *
##***
#ccopia destroy
#initcopy ccopia = cNEO
#ccopia print_c
* *
   
***
##* *
##   
##***
#ccopia destroy
###!
###!
###!------------------------------------------------------------------
###3 Cambra: copia
###!------------------------------------------------------------------
###!
#init ccopia cambra
#ccopia = cNEO
#ccopia print_c
* *
   
***
##* *
##   
##***
#ccopia destroy
###!
###!
###!------------------------------------------------------------------
###4 Cambra: porta_oberta
###!------------------------------------------------------------------
###!
#c porta_oberta N
false
##false
#c porta_oberta E
false
##false
#c porta_oberta O
false
##false
#c porta_oberta S
false
##false
###!
#cN porta_oberta N
true
##true
#cN porta_oberta E
false
##false
#cN porta_oberta O
false
##false
#cN porta_oberta S
false
##false
###!
#cE porta_oberta N
false
##false
#cE porta_oberta E
true
##true
#cE porta_oberta O
false
##false
#cE porta_oberta S
false
##false
###!
#cO porta_oberta N
false
##false
#cO porta_oberta E
false
##false
#cO porta_oberta O
true
##true
#cO porta_oberta S
false
##false
###!
#cNES porta_oberta N
true
##true
#cNES porta_oberta E
true
##true
#cNES porta_oberta O
false
##false
#cNES porta_oberta S
true
##true
###!
#cESO porta_oberta N
false
##false
#cESO porta_oberta E
true
##true
#cESO porta_oberta O
true
##true
#cESO porta_oberta S
true
##true
###!
#cNESO porta_oberta N
true
##true
#cNESO porta_oberta E
true
##true
#cNESO porta_oberta O
true
##true
#cNESO porta_oberta S
true
##true
###!
#cNESO porta_oberta norte
false
##false
#cNESO porta_oberta NO_DIR
false
##false
#c porta_oberta NO_DIR
false
##false
###!
###!
###!------------------------------------------------------------------
###5 Cambra: obre_porta_c
###!------------------------------------------------------------------
###!
#c obre_porta_c N
#c print_c
* *
* *
***
##* *
##* *
##***
#c obre_porta_c E
#c print_c
* *
*  
***
##* *
##*  
##***
#c obre_porta_c O
#c print_c
* *
   
***
##* *
##   
##***
#c obre_porta_c S
#c print_c
* *
   
* *
##* *
##   
##* *
#c obre_porta_c S
#c print_c
* *
   
* *
##* *
##   
##* *
#c obre_porta_c Sur
Error::cambra:20:La paret no existeix.
##Error::cambra:20:La paret no existeix.
#c obre_porta_c NO_DIR
Error::cambra:20:La paret no existeix.
##Error::cambra:20:La paret no existeix.
###!
###!
###!------------------------------------------------------------------
###6 Cambra: tanca_porta_c
###!------------------------------------------------------------------
###!
#c tanca_porta_c N
#c print_c
***
   
* *
##***
##   
##* *
#c tanca_porta_c S
#c print_c
***
   
***
##***
##   
##***
#c tanca_porta_c O
#c print_c
***
*  
***
##***
##*  
##***
#c tanca_porta_c E
#c print_c
***
* *
***
##***
##* *
##***
#c tanca_porta_c E
#c print_c
***
* *
***
##***
##* *
##***
#c tanca_porta_c Norte
Error::cambra:20:La paret no existeix.
##Error::cambra:20:La paret no existeix.
#c tanca_porta_c NO_DIR
Error::cambra:20:La paret no existeix.
##Error::cambra:20:La paret no existeix.
###!
###!
###!------------------------------------------------------------------
###7 Cambra: ==
###!------------------------------------------------------------------
###!
#cNE == cNE
true
##true
#cN == cNE
false
##false
#c == c
true
##true
#cNESO == cNESO
true
##true
#initcopy cSOcopia = cSO
#cSOcopia == cSO
true
##true
#cSOcopia obre_porta_c N
#cSOcopia == cSO
false
##false
#cSOcopia == cSON
true
##true
###!
###!
###!------------------------------------------------------------------
###8 Cambra: !=
###!------------------------------------------------------------------
###!
#cNE != cNE
false
##false
#cN != cNE
true
##true
#c != c
false
##false
#cNESO != cNESO
false
##false
#initcopy cSOcopia = cSO
#cSOcopia != cSO
false
##false
#cSOcopia obre_porta_c N
#cSOcopia != cSO
true
##true
#cSOcopia != cSON
false
##false
#cSOcopia destroy
###!
###!
###!------------------------------------------------------------------
###9 Cambra: <
###!------------------------------------------------------------------
###!
#cN < cNE
true
##true
#cNE < cSO
false
##false
###!
###!
###!------------------------------------------------------------------
###10 Cambra: destruccio
###!------------------------------------------------------------------
###!
#c destroy
#cN destroy
#cE destroy
#cS destroy
#cO destroy
#cNE destroy
#cNS destroy
#cNO destroy 
#cES destroy
#cEO destroy
#cSO destroy
#cNES destroy
#cNEO destroy
#cESO destroy
#cSON destroy
#cNESO destroy
###!
###! Fi del joc de proves de cambra
###!
###!
#load jp_public_laberint.in
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
###!
#load jp_public_particio.in
###!---------------------------------------------------------------------
###!
###! JOC DE PROVES DE PARTICIO<T>
###!
###! Provarem la particio amb enters (si funciona correctament
###! amb enters, tambe ho fara amb altres tipus).
###!---------------------------------------------------------------------
###!
###!
###!---------------------------------------------------------------------
###1 Particio de 1, 2 i 9 elements
###!---------------------------------------------------------------------
###!
###!---------------------------------------------------------------------
###1.1 Constructor i insercio
###!---------------------------------------------------------------------
###!
###! Constructor particio buida
#init p0 particio<int> 0
###! Intentem inserir element sobrepassant maxim
#p0 afegir 1
Error::particio<T>:41:Particio plena.
##Error::particio<T>:41:Particio plena.
###!
###! Constructor particio amb 1 element
#init p1 particio<int> 1
#p1 afegir 3
###! Intentem inserir element sobrepassant maxim
#p1 afegir 1
Error::particio<T>:41:Particio plena.
##Error::particio<T>:41:Particio plena.
###!
###! Constructor particio amb 2 elements pero espai per 9 elements
#init p2 particio<int> 9
#p2 afegir 3
#p2 afegir 7
###!
###! Constructor particio amb multiples elements
#init p9 particio<int> 9
#p9 afegir 3
#p9 afegir 79
#p9 afegir 5
#p9 afegir 10
#p9 afegir 2
#p9 afegir 9
#p9 afegir 4
#p9 afegir 12
#p9 afegir 15
###! Intentem inserir element repetit
#p9 afegir 5
###! Intentem inserir element sobrepassant maxim
#p9 afegir 1
Error::particio<T>:41:Particio plena.
##Error::particio<T>:41:Particio plena.
###!
###!---------------------------------------------------------------------
###1.2 Consultora numero blocs
###!---------------------------------------------------------------------
###!
#p0 size
0
##0
#p1 size
1
##1
#p2 size
2
##2
#p9 size
9
##9
###!
###!---------------------------------------------------------------------
###1.3 Consultora numero elements i numero maxim
###!---------------------------------------------------------------------
###!
#p0 num_elems
0
##0
#p0 num_maxim
0
##0
###!
###!
#p1 num_elems
1
##1
#p1 num_maxim
1
##1
###!
###!
#p2 num_elems
2
##2
#p2 num_maxim
9
##9
###!
###!
#p9 num_elems
9
##9
#p9 num_maxim
9
##9
###!
###!---------------------------------------------------------------------
###1.4 Unio de blocs
###!---------------------------------------------------------------------
###!
#p0 unir 0 0
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p0 unir 1 1
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
###!
###!
#p1 unir 0 1
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 unir 3 0
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 unir 2 3
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 unir 3 3
###!
###!
#p2 unir 0 7
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p2 unir 7 4
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p2 unir 7 7
#p2 unir 7 3
#p2 unir 3 7
###!
###!
#p9 unir 0 5
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 unir 5 6
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 unir 12 3
#p9 unir 5 9
#p9 unir 15 5
###!
###!---------------------------------------------------------------------
###1.5 Elements pertanyen al mateix bloc
###!---------------------------------------------------------------------
###!
#p0 equiv 0 0
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p0 equiv 1 1
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
###!
###!
#p1 equiv 0 1
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 equiv 3 0
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 equiv 2 3
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 equiv 3 3
true
##true
###!
###!
#p2 equiv 0 7
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p2 equiv 7 4
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p2 equiv 7 7
true
##true
#p2 equiv 7 3
true
##true
#p2 equiv 3 7
true
##true
###!
###!
#p9 equiv 0 5
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 equiv 5 6
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 equiv 12 3
true
##true
#p9 equiv 3 12
true
##true
#p9 equiv 5 9
true
##true
#p9 equiv 15 5
true
##true
#p9 equiv 9 15
true
##true
#p9 equiv 15 9
true
##true
#p9 equiv 2 2
true
##true
#p9 equiv 15 15
true
##true
#p9 equiv 2 3
false
##false
#p9 equiv 5 12
false
##false
#p9 equiv 10 15
false
##false
#p9 equiv 5 4
false
##false
###!
###!---------------------------------------------------------------------
###1.6 Consultora numero blocs (despres de fer unions)
###!---------------------------------------------------------------------
###!
#p0 size
0
##0
#p1 size
1
##1
#p2 size
1
##1
#p9 size
6
##6
###!
###!---------------------------------------------------------------------
###1.7 Consultora numero elements i numero maxim sobre 
###!   copies de particio (despres de fer unions)
###!---------------------------------------------------------------------
###!
#p0 num_elems
0
##0
#p0 num_maxim
0
##0
###!
###!
#p1 num_elems
1
##1
#p1 num_maxim
1
##1
###!
###!
#p2 num_elems
2
##2
#p2 num_maxim
9
##9
###!
###!
#p9 num_elems
9
##9
#p9 num_maxim
9
##9
###!
###!---------------------------------------------------------------------
###2 Constructors per copia, destructores i assignacio
###!---------------------------------------------------------------------
###!
###!---------------------------------------------------------------------
###2.1 Inicialitzacions
###!---------------------------------------------------------------------
###!
#initcopy pp0 = p0
#initcopy pp1 = p1
#initcopy pp2 = p2
#initcopy pp9 = p9
#p0 destroy
#p1 destroy
#p2 destroy
#p9 destroy
#init p0 particio<int> 10
#init p1 particio<int> 10
#init p2 particio<int> 10
#init p9 particio<int> 10
#p0 = pp0
#p1 = pp1
#p2 = pp2
#p9 = pp9
#pp0 destroy
#pp1 destroy
#pp2 destroy
#pp9 destroy
###!
###!---------------------------------------------------------------------
###2.2 Consultora numero blocs sobre copies de particio
###!---------------------------------------------------------------------
###!
#p0 size
0
##0
#p1 size
1
##1
#p2 size
1
##1
#p9 size
6
##6
###!
###!---------------------------------------------------------------------
###2.3 Consultora numero elements i numero maxim sobre copies de particio
###!---------------------------------------------------------------------
###!
#p0 num_elems
0
##0
#p0 num_maxim
0
##0
###!
###!
#p1 num_elems
1
##1
#p1 num_maxim
1
##1
###!
###!
#p2 num_elems
2
##2
#p2 num_maxim
9
##9
###!
###!
#p9 num_elems
9
##9
#p9 num_maxim
9
##9
###!
###!---------------------------------------------------------------------
###2.4 Unio de blocs sobre copies de particio
###!---------------------------------------------------------------------
###!
#p9 unir 0 5
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 unir 5 6
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 unir 4 2
#p9 unir 2 9
###!
###!---------------------------------------------------------------------
###2.5 Elements pertanyen al mateix bloc sobre copies de particio
###!---------------------------------------------------------------------
###!
#p0 equiv 0 0
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p0 equiv 1 1
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
###!
###!
#p1 equiv 0 1
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 equiv 3 0
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 equiv 2 3
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p1 equiv 3 3
true
##true
###!
###!
#p2 equiv 0 7
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p2 equiv 7 4
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p2 equiv 7 7
true
##true
#p2 equiv 7 3
true
##true
#p2 equiv 3 7
true
##true
###!
###!
#p9 equiv 0 5
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 equiv 5 6
Error::particio<T>:40:L'element no pertany a la particio.
##Error::particio<T>:40:L'element no pertany a la particio.
#p9 equiv 12 3
true
##true
#p9 equiv 3 12
true
##true
#p9 equiv 5 9
true
##true
#p9 equiv 15 5
true
##true
#p9 equiv 9 15
true
##true
#p9 equiv 15 9
true
##true
#p9 equiv 2 2
true
##true
#p9 equiv 15 15
true
##true
#p9 equiv 2 3
false
##false
#p9 equiv 5 12
false
##false
#p9 equiv 10 15
false
##false
#p9 equiv 5 4
true
##true
###!
###!---------------------------------------------------------------------
###2.6 Consultora numero blocs (despres de fer unions)
###!---------------------------------------------------------------------
###!
#p0 size
0
##0
#p1 size
1
##1
#p2 size
1
##1
#p9 size
4
##4
###!
###!---------------------------------------------------------------------
###2.7 Consultora numero elements i numero maxim sobre 
###!   copies de particio (despres de fer unions)
###!---------------------------------------------------------------------
###!
#p0 num_elems
0
##0
#p0 num_maxim
0
##0
###!
###!
#p1 num_elems
1
##1
#p1 num_maxim
1
##1
###!
###!
#p2 num_elems
2
##2
#p2 num_maxim
9
##9
###!
###!
#p9 num_elems
9
##9
#p9 num_maxim
9
##9
###!
#p0 destroy
#p1 destroy
#p2 destroy
#p9 destroy
###!
###! Fi del joc de proves de particio
###!
###!
#load jp_public_dedalus.in
###!------------------------------------------------------------------
###! JOC DE PROVES DE DEDALUS
###!------------------------------------------------------------------
###!
###!
###!------------------------------------------------------------------
###1 Inicialitzacions
###!------------------------------------------------------------------
###!
#init l3x1 laberint 3 1
#init l3x11 laberint 3 11
#init l5x5 laberint 5 5
###!
###!
###!------------------------------------------------------------------
###2 Construccio de laberints
###!------------------------------------------------------------------
###!
#l3x1 construir
dedalus::construir OK
##dedalus::construir OK
#l3x1 comprova_perfecte
true
##true
#l3x1 print
3 1
***
* *
* *
* *
* *
* *
***
##3 1
##***
##* *
##* *
##* *
##* *
##* *
##***
###!
#l3x11 construir
dedalus::construir OK
##dedalus::construir OK
#l3x11 comprova_perfecte
true
##true
###!
#l5x5 construir
dedalus::construir OK
##dedalus::construir OK
#l5x5 comprova_perfecte
true
##true
###!
#l3x1 destroy
#l3x11 destroy
#l5x5 destroy
###!
###! Fi del joc de proves de dedalus
###!
###!
#load jp_public_teseus.in
###!------------------------------------------------------------------
###! JOC DE PROVES DE TESEUS
###!---------------------------------------------------------------------
###!
###!
###!---------------------------------------------------------------------
###1 Laberints sense portes
###!---------------------------------------------------------------------
###!
#init lab1x1 laberint 1 1
#buscar 0 1 1 1
Error::teseus:61:La cambra inicial o final no es valida.
##Error::teseus:61:La cambra inicial o final no es valida.
#buscar 1 1 1 1
[(1,1)]
##[(1,1)]
###!
#init lab2x5 laberint 2 5
#buscar 1 2 1 1
Error::teseus:60:El laberint no te solucio.
##Error::teseus:60:El laberint no te solucio.
#buscar 1 6 1 1
Error::teseus:61:La cambra inicial o final no es valida.
##Error::teseus:61:La cambra inicial o final no es valida.
#buscar 1 1 1 1
[(1,1)]
##[(1,1)]
#buscar 2 1 2 1
[(2,1)]
##[(2,1)]
###!
#init lab3x3 laberint 3 3
#buscar 1 1 2 1
Error::teseus:60:El laberint no te solucio.
##Error::teseus:60:El laberint no te solucio.
#buscar 1 1 6 1  
Error::teseus:61:La cambra inicial o final no es valida.
##Error::teseus:61:La cambra inicial o final no es valida.
#buscar 1 1 1 1
[(1,1)]
##[(1,1)]
#buscar 3 3 3 3
[(3,3)]
##[(3,3)]
###!
#init lab5x2 laberint 5 2
#buscar 1 1 1 2
Error::teseus:60:El laberint no te solucio.
##Error::teseus:60:El laberint no te solucio.
#buscar 1 1 1 6
Error::teseus:61:La cambra inicial o final no es valida.
##Error::teseus:61:La cambra inicial o final no es valida.
#buscar 1 1 1 1
[(1,1)]
##[(1,1)]
#buscar 2 1 2 1
[(2,1)]
##[(2,1)]
#buscar 3 2 3 2
[(3,2)]
##[(3,2)]
#buscar 5 2 5 2
[(5,2)]
##[(5,2)]
###!
###!
#lab1x1 destroy
#lab2x5 destroy
#lab3x3 destroy
#lab5x2 destroy
###!
###!
###!---------------------------------------------------------------------
###2 Laberint 3x3 sense cicles
###!---------------------------------------------------------------------
###!
#init lab_unic laberint ./laberint_3x3.txt
#buscar 1 1 3 3
[(1,1),(1,2),(2,2),(3,2),(3,3)]
##[(1,1),(1,2),(2,2),(3,2),(3,3)]
#buscar 1 2 2 3
Error::teseus:60:El laberint no te solucio.
##Error::teseus:60:El laberint no te solucio.
#buscar 1 2 2 1
Error::teseus:60:El laberint no te solucio.
##Error::teseus:60:El laberint no te solucio.
#buscar 1 2 1 3
Error::teseus:60:El laberint no te solucio.
##Error::teseus:60:El laberint no te solucio.
#buscar 2 1 3 1
[(2,1),(3,1)]
##[(2,1),(3,1)]
#lab_unic destroy
###!
###!
###!---------------------------------------------------------------------
###3 Laberint 3x3 amb cicles
###!---------------------------------------------------------------------
###!
#init lab_cicle laberint ./laberint_3x3_cicles.txt
#buscar 1 3 3 3
[(1,3),(2,3),(3,3)]
##[(1,3),(2,3),(3,3)]
#buscar 1 2 2 3
[(1,2),(1,3),(2,3)]
##[(1,2),(1,3),(2,3)]
#buscar 1 2 2 1
[(1,2),(2,2),(2,1)]
##[(1,2),(2,2),(2,1)]
#comprova_cami_minim 1 2 3 3
true
##true
#lab_cicle destroy
###!
###!
###!---------------------------------------------------------------------
###4 Laberint 30x30 sense cicles
###!---------------------------------------------------------------------
###!
#init lab_gran laberint ./laberint_30x30.txt
#buscar 1 3 3 3
[(1,3),(1,4),(1,5),(2,5),(2,4),(2,3),(3,3)]
##[(1,3),(1,4),(1,5),(2,5),(2,4),(2,3),(3,3)]
#buscar 1 2 2 3
[(1,2),(2,2),(2,3)]
##[(1,2),(2,2),(2,3)]
#buscar 1 2 2 1
[(1,2),(1,1),(2,1)]
##[(1,2),(1,1),(2,1)]
#buscar 10 20 22 14
[(10,20),(10,21),(9,21),(9,22),(8,22),(7,22),(6,22),(5,22),(4,22),(3,22),(3,21),(4,21),(5,21),(5,20),(4,20),(4,19),(5,19),(6,19),(6,20),(7,20),(7,19),(8,19),(9,19),(10,19),(11,19),(11,18),(11,17),(12,17),(12,16),(12,15),(13,15),(13,16),(14,16),(14,17),(15,17),(15,16),(15,15),(16,15),(17,15),(18,15),(19,15),(20,15),(21,15),(21,14),(22,14)]
##[(10,20),(10,21),(9,21),(9,22),(8,22),(7,22),(6,22),(5,22),(4,22),(3,22),(3,21),(4,21),(5,21),(5,20),(4,20),(4,19),(5,19),(6,19),(6,20),(7,20),(7,19),(8,19),(9,19),(10,19),(11,19),(11,18),(11,17),(12,17),(12,16),(12,15),(13,15),(13,16),(14,16),(14,17),(15,17),(15,16),(15,15),(16,15),(17,15),(18,15),(19,15),(20,15),(21,15),(21,14),(22,14)]
#buscar 30 30 1 1
[(30,30),(30,29),(30,28),(29,28),(29,27),(29,26),(29,25),(28,25),(28,26),(27,26),(26,26),(26,25),(27,25),(27,24),(27,23),(28,23),(29,23),(29,22),(28,22),(28,21),(29,21),(29,20),(28,20),(27,20),(27,19),(26,19),(26,20),(25,20),(25,19),(24,19),(24,20),(23,20),(22,20),(21,20),(21,19),(20,19),(19,19),(18,19),(17,19),(16,19),(16,18),(16,17),(17,17),(17,16),(17,15),(18,15),(19,15),(19,14),(19,13),(19,12),(19,11),(19,10),(19,9),(20,9),(21,9),(21,10),(22,10),(22,9),(23,9),(23,8),(23,7),(23,6),(22,6),(22,5),(22,4),(22,3),(21,3),(21,4),(21,5),(20,5),(19,5),(19,4),(18,4),(18,5),(17,5),(17,4),(16,4),(16,3),(16,2),(15,2),(15,3),(15,4),(14,4),(14,5),(13,5),(12,5),(12,6),(11,6),(10,6),(9,6),(8,6),(8,7),(7,7),(6,7),(6,6),(5,6),(5,5),(6,5),(7,5),(7,4),(7,3),(7,2),(8,2),(8,1),(7,1),(6,1),(5,1),(4,1),(3,1),(2,1),(1,1)]
##[(30,30),(30,29),(30,28),(29,28),(29,27),(29,26),(29,25),(28,25),(28,26),(27,26),(26,26),(26,25),(27,25),(27,24),(27,23),(28,23),(29,23),(29,22),(28,22),(28,21),(29,21),(29,20),(28,20),(27,20),(27,19),(26,19),(26,20),(25,20),(25,19),(24,19),(24,20),(23,20),(22,20),(21,20),(21,19),(20,19),(19,19),(18,19),(17,19),(16,19),(16,18),(16,17),(17,17),(17,16),(17,15),(18,15),(19,15),(19,14),(19,13),(19,12),(19,11),(19,10),(19,9),(20,9),(21,9),(21,10),(22,10),(22,9),(23,9),(23,8),(23,7),(23,6),(22,6),(22,5),(22,4),(22,3),(21,3),(21,4),(21,5),(20,5),(19,5),(19,4),(18,4),(18,5),(17,5),(17,4),(16,4),(16,3),(16,2),(15,2),(15,3),(15,4),(14,4),(14,5),(13,5),(12,5),(12,6),(11,6),(10,6),(9,6),(8,6),(8,7),(7,7),(6,7),(6,6),(5,6),(5,5),(6,5),(7,5),(7,4),(7,3),(7,2),(8,2),(8,1),(7,1),(6,1),(5,1),(4,1),(3,1),(2,1),(1,1)]
#buscar 1 1 30 30
[(1,1),(2,1),(3,1),(4,1),(5,1),(6,1),(7,1),(8,1),(8,2),(7,2),(7,3),(7,4),(7,5),(6,5),(5,5),(5,6),(6,6),(6,7),(7,7),(8,7),(8,6),(9,6),(10,6),(11,6),(12,6),(12,5),(13,5),(14,5),(14,4),(15,4),(15,3),(15,2),(16,2),(16,3),(16,4),(17,4),(17,5),(18,5),(18,4),(19,4),(19,5),(20,5),(21,5),(21,4),(21,3),(22,3),(22,4),(22,5),(22,6),(23,6),(23,7),(23,8),(23,9),(22,9),(22,10),(21,10),(21,9),(20,9),(19,9),(19,10),(19,11),(19,12),(19,13),(19,14),(19,15),(18,15),(17,15),(17,16),(17,17),(16,17),(16,18),(16,19),(17,19),(18,19),(19,19),(20,19),(21,19),(21,20),(22,20),(23,20),(24,20),(24,19),(25,19),(25,20),(26,20),(26,19),(27,19),(27,20),(28,20),(29,20),(29,21),(28,21),(28,22),(29,22),(29,23),(28,23),(27,23),(27,24),(27,25),(26,25),(26,26),(27,26),(28,26),(28,25),(29,25),(29,26),(29,27),(29,28),(30,28),(30,29),(30,30)]
##[(1,1),(2,1),(3,1),(4,1),(5,1),(6,1),(7,1),(8,1),(8,2),(7,2),(7,3),(7,4),(7,5),(6,5),(5,5),(5,6),(6,6),(6,7),(7,7),(8,7),(8,6),(9,6),(10,6),(11,6),(12,6),(12,5),(13,5),(14,5),(14,4),(15,4),(15,3),(15,2),(16,2),(16,3),(16,4),(17,4),(17,5),(18,5),(18,4),(19,4),(19,5),(20,5),(21,5),(21,4),(21,3),(22,3),(22,4),(22,5),(22,6),(23,6),(23,7),(23,8),(23,9),(22,9),(22,10),(21,10),(21,9),(20,9),(19,9),(19,10),(19,11),(19,12),(19,13),(19,14),(19,15),(18,15),(17,15),(17,16),(17,17),(16,17),(16,18),(16,19),(17,19),(18,19),(19,19),(20,19),(21,19),(21,20),(22,20),(23,20),(24,20),(24,19),(25,19),(25,20),(26,20),(26,19),(27,19),(27,20),(28,20),(29,20),(29,21),(28,21),(28,22),(29,22),(29,23),(28,23),(27,23),(27,24),(27,25),(26,25),(26,26),(27,26),(28,26),(28,25),(29,25),(29,26),(29,27),(29,28),(30,28),(30,29),(30,30)]
#lab_gran destroy
###!
###! Fi del joc de proves de teseus
###!
#exit
[0/0]**
