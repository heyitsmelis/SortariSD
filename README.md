# SortariSD
Aceasta este tema 1 pentru Structuri De Date, rezolvata in C++.
In continuare voi prezenta tipuri de sortari implementate,cele mai favorabie si defavorabile cazuri pentru folosinta acestora dar si o comparatie intre timpii de rulare ale testelor.

1.Bubblesort: ideea fundamentala este de a interschimba in mod repetat elementele vectorului pana la sortarea acestuia.
Cel mai bun caz este O(n), iar cel mai rau O(n^2)

2.Countsort: se bazeaza pe utilizarea unui vector de frecventa
Complexitatea sa este O(n+k)

3.Mergesort: se imparte vectorul in jumatati pana cand se ajunge la perechi de cate doua elemente, urmand ca acestea sa fie sortate, iar apoi perechile se interclaseaza.
Complexitatea sa este O(n log n)

4.Quicksort: se alege un pivot, se ordoneaza elementele vectorului, astfel incat toate elementele din stanga sa sa fie mai mici sau egale, iar elementele din dreapta mai mari sau egale.
Cel mai bun caz este O(n log n), iar cel mai rau O(n^2)

5.Radixsort: la fel ca si Mergesort, acesta are la baza divide et impera si interclasarea.
Cel mai bun caz este O((n+256)*log256(k)), iar cel mai rau O(256)

6.Shellsort: se sorteaza perechi de elemente la pozitii la distante mari una de cealalta, apoi reducand diferenta dintre elementele comparate.
Cel mai bun caz este O(n log n), iar cel mai rau este O(n^2)

In functie de numarul de elemente cele mai ineficiente sortari sunt Bubblesort si Quicksort. 
In functie de maximul gasit in vector cele ineficiente sortari sunt BubbleSort, CountSort si Quicksort
Cele mai ineficiente sortari pentru N = 10^8 si maxx = 10^8 sunt MergeSort, Quicksort si bubblesort.
