## Treść projektu
Przedstawiony algorytm realizuje następujące zagadnienia:
- wczytanie dowolnego grafu skierowanego z pliku tekstowego
− sprawdzenie, czy wczytany graf jest grafem sprzężonym
− jeśli graf jest grafem sprzężonym, sprawdzenie, czy jest grafem liniowym
− wypisanie komunikatu o wyniku powyższego sprawdzenia
− jeśli graf jest grafem sprzężonym, przekształcenie go w jego graf oryginalny (H)
− zapisanie grafu wynikowego H do pliku tekstowego w tym samym formacie
### Format wejściowy
Plik z danymi wejściowymi (reprezentacja grafu sprzężonego) został przygotowany w taki
sposób aby umożliwić proste wprowadzanie istotnych dla programu danych tj. liczba
wierzchołków i krawędzi w grafie oraz ilość następników każdego wierzchołka.

W pierwszej linii znajdują się kolejno liczba wierzchołków i liczba krawędzi w grafie,
oddzielone spacją. Następne wiersze przechowują informacje dotyczące struktury grafu
wejściowego:
- pierwsza wartość to liczba następników tego wierzchołka
- kolejno wypisane liczby to indeksy następników
  
Wszystkie wartości oddzielone są od siebie spacjami, a nowa linia koduje kolejny
wierzchołek. Ważne jest, aby w pliku nie znajdowały się żadne puste linie, a wszystkie dane
były wprowadzane poprawnie.

W przypadku, gdy dany wierzchołek nie ma następników, w wierszu mu odpowiadającym
znajduję się tylko liczba 0 (oznaczająca liczbę następników).
### Graf orginalny 
Rozwiązanie problemu tzn. graf oryginalny zostaje zapisany do pliku o nazwie wynik.txt w
identycznym formacie, jak graf wejściowy wraz z informacją o liczbie wierzchołków i
krawędzi.
### Złożoność obliczeniowa
Procedura odczytu oraz zapisu do pliku posiadają zależność w czasie liniowym O(n + m),
gdzie n to liczba wierzchołków, a m to liczba krawędzi. W funkcji oceniającej sprzężoność
grafu porównywane są wszystkich kombinacje par wierzchołków, co prowadzi do złożoności wielomianowej. 
Jest to zatem algorytm dokładny o złożoności wielomianowej.

