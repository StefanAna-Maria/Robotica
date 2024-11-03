# Robotica - Tema 2 - TypeRacer Game
## 1.1 Descrierea functionalitatii proiectului: 
Acest proiect este un joculet asemanator cu TypeRacer.


## 1.2 Componentele utilizate
In realizarea montajului am utilizat urmatoarele componente:
- Breadboard
- 1x LED RGB
- 2x butoane (1 buton de start/stop si 1 buton pentru selectarea dificultatii jocului)
- Un total de 5 rezistoare dintre care:
* 3 cu valoarea = 330 ohm
* 2 cu valoarea = 1K
- 10x fire pentru legaturi
- Placuta de Arduino UNO din kit-ul primit 
## 2)Cerinte:
<details> 
<summary>2.1 Detalii tehnice</summary>
  <details>
  <summary>LED RGB - Indicator de stare:</summary>

  - În starea de repaus, LED-ul va avea culoarea albă.
  - La apăsarea butonului de start, LED-ul va clipi timp de 3 secunde, indicând o numărătoare inversă până la începerea rundei.
  - În timpul unei runde: LED-ul va fi verde dacă textul introdus este corect și va deveni roșu în caz de greșeală.
  </details>
  <details>
  <summary>Butonul Start/Stop:</summary>
    
  - Modul de repaus: Dacă jocul este oprit, apăsarea butonului inițiază o nouă rundă după o numărătoare inversă de 3 secunde.
  - În timpul unei runde: Dacă runda este activă, apăsarea butonului o va opri imediat.
  </details>
  <details>
  <summary>Butonul de dificultate:</summary>
  
  - Butonul de dificultate controlează viteza cu care apar cuvintele și poate fi folosit doar în starea de repaus.
  - La fiecare apăsare, dificultatea se schimbă ciclind între: (Easy, Medium, Hard).
  - La schimbarea dificultății, se trimite un mesaj prin serial: “Easy/Medium/Hard mode on!”.
  </details>
  <details>
  <summary>Generarea cuvintelor:</summary>
  
  - Se va crea un dicționar de cuvinte.
  - În timpul unei runde, cuvintele vor fi afișate în terminal într-o ordine aleatorie.
  - Dacă cuvântul curent a fost scris corect, un cuvânt nou va fi afișat imediat. Dacă nu, un nou cuvânt va apărea după intervalul de timp stabilit în funcție de dificultate.
  </details>
  <details>
  <summary>Alte observații:</summary>
  
  - Timpul alocat pentru o rundă este de 30 de secunde.
  - La sfârșitul fiecărei runde, se va afișa în terminal câte cuvinte au fost scrise corect.
  </details>
</details>
<details>
<summary> 2.2 Flow-ul procesului: </summary>

1. Jocul este în repaus. LED-ul RGB are culoarea albă.

2. Se alege dificultatea jocului folosind butonul de dificultate, iar în terminal va apărea “Easy/Medium/Hard mode on!”.

3. Se apasă butonul de start/stop.

4. LED-ul clipește timp de 3 secunde, iar în terminal se va afișa numărătoarea înversă: 3, 2, 1.

5. LED-ul devine verde și încep să apară cuvinte de tastat.

6. La tastarea corectă, următorul cuvânt apare imediat. Dacă nu se tasteaza cuvântul în timpul stabilit de dificultate, va apărea un nou cuvânt.

7. O greșeală face LED-ul să devină roșu. Pentru a corecta cuvântul, se va folosi tasta BackSpace.

8. Dupa 30 de secunde, runda se termină, iar în terminal se va afișa scorul: numărul total de cuvinte scrise corect.

9. Jocul se poate opri oricând cu butonul de start/stop.
</details>

## 3)Schema electrica:
![Screenshot 2024-11-03 033942](https://github.com/user-attachments/assets/14c0e529-ce24-4640-ba20-aa28a05dbc6b)

## 4)Poze montaj fizic:

## 5)Link video:


