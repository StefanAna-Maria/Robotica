# TEMA 3 - Quick Time Game
-> Coechipier: [Hera Andreea-Diana](https://github.com/DianaHera) :)

## Descriere
Aceasta tema consta in dezvoltarea unui joc competitiv de reflex pentru doi jucatori, in care participantii isi testeaza viteza reflexelor in incercarea de a obtine un scor cat mai mare.

Fiecare jucător dispune de un set de 3 butoane, 3 LED-uri simple si un LED RGB, iar jocul se desfasoara pe parcursul mai multor runde. Scopul fiecarui jucator este sa apese cat mai rapid butonul care corespunde culorii afisate de LED-ul sau RGB. Punctajul fiecarui jucător va fi afisat si actualizat in timp real pe monitorul serial, iar la finalul jocului se afiseaza scorul final al ambilor jucatori pe LCD si jucatorul cu cel mai mare punctaj va fi declarat castigator.

## Componente Utilizate:
- **6x LED-uri**
- **2x LED RGB** (cate unul pentru fiecare jucator)
- **7x butoane** (cate 3 pentru fiecare jucător si unul de start)
- **1x ecran LCD**
- **1x servomotor**
- **2x breadboard**
- **Fire de legătură**
- **2x Arduino Uno**
- **1X potentiometru**
- **1x buzzer**
- **8x rezistoare de 1 kOhm
- **13x rezistoare de 330 Ohm
- **1x rezistoare de 100 Ohm

## Flow-ul Jocului

<details>
<summery> 1. Inițializare </summery>

- La inceput pe LCD este afisat un mesaj de bun venit.
- Jocul se porneste prin apasarea butonului de start de pe placa "Master".
- Dupa pornire vor aparea atat pe LCD cat si in monitorul serial mesaje pentru introducerea numelor jucatorilor.
- Dupa inregistrarea ambelor nume se vor afisa pe LCD numele celor care se vor duela, apoi vor incepe rundele.
</details>

<details>
<summary> 2. Desfășurarea Rundelor </summary>

- Fiecare jucator are trei butoane, fiecare asociat unui LED de o culoare distincta, și un LED RGB.
- Rundele dureaza cate o secunda si alterneaza intre cei 2 jucatori.
- In fiecare runda, jucatorul activ va urmari LED-ul RGB aprins intr-o culoare corespunzatoare unuia dintre butoanele sale. - Jucatorul trebuie sa apese cat mai rapid butonul corect pentru a acumula puncte.
- Cu cat reactioneaza mai repede, cu atat scorul este mai mare.
- Pe parcursul jocului, ecranul LCD va afisa alternativ numele jucatorilor atunci cand sunt activi.
</details>

<details>
<summary> 3. Finalizarea Jocului </summary>

- Servomotorul se roteste in timpul jocului pentru a indica progresul. O rotatie completa marcheaza sfarsitul jocului.
- La final, LCD-ul afișează scorul final al fiecarui jucator pentru cateva secunde, iar apoi castigatorul si revine la mesajul de bun venit.
</details>

## Detalii Tehnice
<details>
<summary> 1. Comunicarea SPI </summary> 

- Din cauza numarului mare de legaturi necesare am folosit 2 placute Arduino pe care le am declarat pe una "Master", iar pe cealalta "Slave" si care comunica intre ele prin SPI.
- Arduino-ul "Master" controlează ecranul LCD, servomotorul si butonul de start. De asemenea, acesta gestioneaza logica jocului, inclusiv scorul.
- Arduino-ul "Slave" gestioneaza butoanele pentru jucatori si LED-urile, primind instructiuni de la "Master" si trimitand inapoi informatii despre butoanele apasate.
</details>

<details>
<summary> 2. Butoanele </summary>
Noi am ales sa utilizam pentru aceasta tema 7 butoane:

  - Am folosit un buton izolat pentru start pe care l-am conectat pe placa "Master".
  - Pentru a ne descurca cu numarul de pini disponibili am ales sa multiplexam totalul de 6 butoane al jucatorilor si sa le conectam pe pinul analogic A0 de pe placa "Slave".
  - Am realizat multiplexarea urmarind: [tutorialul de multiplexare](https://www.youtube.com/watch?v=Y23vMfynUJ0).
</details>

<details>
<summary> 3. LED-uri </summary>

- Led-urile simple stau aprinse pentru a face usoara identificarea corecta a butoanelor corespunzatoare.
- Din lipsa de pini, am legat toate cele 6 Led-uri simple impreuna pe pinul digital 2 al placii "Slave".
- Fiecare LED RGB se va aprinde doar in rundele jucatorului caruia ii corespunde intr-o culoare random din cele 3 care sunt asociate butoanelor.
</details>

<details>
<summary> 4. LCD </summary>

- Este conectat si controlat de placa "Master".
- Am utilizat biblioteca `LiquidCrystal`.
- Setarea luminozității și contrastului se realizeaza utilizand potentiometrul.
- Liniile de date ale LCD-ului sunt conectate la pinii D4-D7.
- LCD-ul va afisa permanent scorurile jucatorilor pe durata jocului.
</details>

<details>
<summary> 5. Servomotor </summary>

- Este conectat si controlat de placa "Master".
- Incepe de la pozitia de 0 grade si se roteste in sens opus acelor de ceasornic pentru a indica progresul timpului.
- Am utilizat biblioteca `Servo.h`.
</details>

<details>
<summary> 6. Buzzer </summary>

- Este conectat si controlat de placa "Slave".
- Scopul acestuia este sa semnaleze schimbarea rundelor prin scoaterea unui sunet de frecv = 350.  
</details>

## Elemente Personalizabile

<details>
<summary> 1. Punctaj: </summary>

- Am ales un sistem simplu pentru calculul punctajului si anume un sistem de notare (A, B, C, F).
- Cu cat apasarea este mai rapida creste si sansa la o nota cat mai mare.
- Daca nu s-a reusit o apasare corecta in timpul limita al rundei miscarea jucatorului va fi notata cu F.
- Valori numerice pentru note: A = 50, B = 25, C = 10, F = 0.
</details>

<details>
<summary> 2. Timp: </summary>

- Fiecare runda dureaza 1 secunda.
- Jocul se incheie dupa terminarea rotatiei servomotorul (la 30 de secude de la inceputul jocului).
</details>

## Schema electrica: 
![Screenshot 2024-11-19 214257](https://github.com/user-attachments/assets/e8b7754d-07eb-4294-8df7-5b37eb5366ea)

## Imagini montaj:
![poza 1_tema 3](https://github.com/user-attachments/assets/fb60e432-74d0-4a02-9210-0bbadd653244)
![poza 2_tema 3](https://github.com/user-attachments/assets/c5bddb5a-5846-4b90-9f49-1c8a2970cdf0)
![poza 3_tema 3](https://github.com/user-attachments/assets/fe70ec96-fd5f-46d9-9e56-b7ec6715f2ca)
![poza 4_tema 3](https://github.com/user-attachments/assets/c95d1b33-e902-4b77-8d81-c7e920515c79)
![poza 5_tema 3](https://github.com/user-attachments/assets/925a67ce-9e26-4fe7-a58d-5c4a2ce0b484)
![poza 6_tema 3](https://github.com/user-attachments/assets/5741c122-79e8-456a-8e10-10a1682747fb)

## Link Video:
[Link Video - tema 3](https://youtu.be/vhr4K7lW5-Y)
