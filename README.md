# Chyrc Maciej Krzysztof

Symulacja pojedynku. Obie postacie wyposażone są w wybrany pancerz i broń (stworzone będzie kilka obiektów jednego i drugiego), elementy te posiadają takie statystyki jak:

- waga - odgrywa rolę przy unikach (postać o zbyt ciężkim wyposażeniu ma utrudnione uniki)
- obrażenia zadawane przez broń
- obrona pancerza - na jego podstawie obliczana jest procentowa redukcja obrażeń otrzymywanych
- równowaga - pancerz ma zadaną stabilność, jaką daje postaci, a broń ma wartość _zbicia_ równowagi wroga, czyli postać z wielkim mieczem może swym atakiem wybić wroga ubranego w skóry z równowagi, ale za to postać wyposażona w sztylet raczej nie zachwieje postawy rycerza w zbroi płytowej.
 
Postacie posiadają za to:
HP - czyli po prostu punkty zdrowia
energia - używana do wyprowadzania ataków i blokowania/unikania tychże, regeneruje się w pewnej ilości co turę, gdy nie wystarcza do obrony, wtedy postać traci równowagę po zablokowaniu ataku i traci następną turę, przez co jest wystawiona na atak bez szansy na obronę (chyba, że wróg chybi, wtedy ma farta).
Walka kończy się oczywiście, gdy jedna postać polegnie.

Argumenty funkcji main:
1: Broń pierwszego wojownika
2: Pancerz pierwszego wojownika
3: Broń drugiego wojownika
4: Pancerz drugiego wojownika

Lista wyposażenia:
a) broń
 1: Straightsword - waga 4.5, obrażenia 210
 2: Greatsword - waga 9, obrażenia 360
 3: Halberd - waga 8, obrażenia 350
 4: Ulumulu - waga 6.66, obrażenia 420
b) pancerz
 1: Knight set - waga 28.5, obrona 170, stabilność 20
 2: Artorias set - waga 18, obrona 140, stabilność 15
 3: Havel set - waga 45, obrona 500, stabilność 50
 4: Thief set - waga 12, obrona 90, stabilność 10
 5: OP - waga 13.37, obrona 666, stabilność 420
 
 2.06: Dodane fight logi, wyeliminowane błędy z traceniem kolejki i dziwnymi werdyktami koncowymi.
 6.06: Dodane instrukcje sprawdzające, czy energia nie wykracza ponad maksimum, naprawiona metoda klasy character sprawiajaca, że ciężki pancerz dawał marginalną ochronę, a lekki mógł zatrzymać nawet samolot lecący na WTC.
 GOTOWE
