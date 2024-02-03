# Hegzy
![](readmeImages/map.png)

**Gra turowa, umiejscowiona na planszy heksagonalnej. W której dwóch graczy naprzemiennie przesuwa jednostki w celu zabicia dru?yny przeciwnej.**

Gra utworzona zosta?a w ramach projektów ko?owych na KNTG poligon, semestr 2018Z

## Autorzy ##
+ @?M?ody - pomys?, mechaniki gry, grafika
+ @?bartek7777 - programowanie


Nale?y podkre?li?, ?e w obecnej wersji gra cechuje si? ograniczon? funkcjonalno?ci?. Reprezentuje ona podstawowe mechaniki trybu bitewnego, ale nie zawiera ca?ego zbioru planowanych rozwi?za?.

Jednostk? reprezentuje sze?cioboczny „?eton” przedstawiaj?cy rysunek jednostki oraz zestaw symboli na poszczególnych bokach.

![](readmeImages/unit.png)

###### Obrót i Ruch  ######
Mechanika poruszania si? jednostek po polu bitwy. Najpierw gracz wybiera przyleg?e *dost?pne (wolne)* pole a ?eton zostaje obrócony w kierunku ruchu.
Sam obrót (nawet w przypadku gdy jednostka ju? wcze?niej by?a obrócona w kierunku ruchu to i tak ten moment jest traktowany jako faza obrotu.

###### Wolne Pole  ######
Jest to ka?de pole nieb?d?ce: ko?cem mapy, przeszkod? terenow?, sojusznicz? jednostk?. Pole z przeciwnikiem traktujemy jako wolne, je?eli ruch, b?dzie skutkowa? usuni?ciem b?d? przesuni?ciem wroga.

###### Symbole  ######
G?ówna mechanika gry reprezentuj?ca umiej?tno?ci jednostki w walce. Symbol zawsze jest umieszczony na poszczególnym boku oznaczaj?cym kierunek.
Symbole dzielimy na dwa rodzaje: *Pasywne* (dzia?aj? w ka?dym momencie) i *Aktywne* (aktywuj? si? podczas: *Obrotu* i *ruchu*). Dzia?anie symbolu nazywane jest *efektem*.
Efekty dzia?aj? w dwóch stanach: pasywnym i aktywnym.
Kiedy jednostka stoi nieruchomo, jej efekty s? w stanie pasywnym. Cz??? efektów dzia?a jedynie w stanie pasywnym. Efekty dzia?aj? na przyleg?e pola wskazane przez symbol przy okre?lonym boku. 
###### Efekty  ######
Efekty aktywne aktywowane zostaj? podczas ruchu dwukrotnie: pierwszy raz w momencie, gdy jednostka obraca si? w kierunku ruchu i drugi raz momencie przej?cia na dane pole.
	Kiedy jednostka si? obraca, przed jej efektami najpierw aktywuj? si? efekty dzia?aj?ce na jej pole.

Gracze naprzemiennie wykonuj? swoje tury, a? jedna ze stron nie b?dzie mia?a jednostek. Strona ta przegrywa, a jej przeciwnik odnosi zwyci?stwo.

###### Zaimplementowane efekty ######
+ ![](readmeImages/Symbol_Spear.png) **W?ócznia** w stanie akrywnym i pasywnym zabija ka?d? jednostk? znajduj?c? si? na przyleg?ym boku.
+ ![](readmeImages/Symbol_Sword.png) **Miecz** w stanie aktywnym zabija ka?d? jednostk? na przyleg?ym boku. 
+ ![](readmeImages/Symbol_Shield.png) **Tarcza** blokuje obra?enie (zniszczenie jednostki) od strony tarczy. 
+ ![](readmeImages/Symbol_Arrow.png) **?uk** w stanie aktywnym wystrzeliwuje pocisk który porusza si? w linii prostej i po natrafieniu na wroga nieos?oni?tego tarcz? zabija go i ko?czy swój “lot”.
+ ![](readmeImages/Symbol_Axe.png) **Topór** w stanie aktywnym wystrzeliwuje pocisk który porusza si? w linii prostej **na odleg?o?? najwy?ej dwóch pól** i po natrafieniu na wroga nieos?oni?tego tarcz? zabija go i ko?czy swój “lot”.
+ ![](readmeImages/Symbol_Push.png) **Odepchni?cie** ignoruj?c tarcze, aktywnie *odpycha* (przesuwa w kierunku naprzeciwleg?y od jednostki aktywnej) wrogie jednostki. Je?eli taka jednostka natrafi na dowolne zaj?te pole lub kraniec mapy, to umiera.
+ ![](readmeImages/Symbol_Hook.png) **Hak** - je?eli 
+ + wroga jednostka znajduje si? w odleg?o?ci od dwóch do trzech pól
+ + pola mi?dzy ni? a postaci? aktywn? s? puste
+  to posta? zostaje przesuni?ta do pola s?siedniego w stosunku do jednostki aktywnej. Pozwoli? to mo?e do "nadziania" wrogiej jednostki na np w?ócznie.