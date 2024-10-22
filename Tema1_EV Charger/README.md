# Robotica - Tema 1 - EV Charger
## 1.1 Descrierea functionalitatii proiectului: 
Acest proiect simulează o stație de încărcare cu indicatori vizuali pentru disponibilitate și nivelul de încărcare a bateriei, utilizând un set de LED-uri RGB și LED-uri simple, alături de un sistem de control bazat pe două butoane pentru start și stop.
<details>
<summary>1) Indicatorul de Disponibilitate (LED RGB)</summary>
  
- Verde: Stația este liberă și gata pentru a începe încărcarea.
- Roșu: Stația este ocupată, iar procesul de încărcare este în desfășurare.
</details>
<details>
<summary>2) Indicatorii de Încărcare a Bateriei (LED-uri Simpe L1, L2, L3, L4)</summary>
Sistemul simulează încărcarea bateriei folosind un loader progresiv reprezentat de patru LED-uri (L1, L2, L3, L4), fiecare indicând un anumit nivel de încărcare:
  
- L1 (25%)
- L2 (50%)
- L3 (75%)
- L4 (100%)

LED-urile se aprind secvențial la intervale fixe de 3 secunde. LED-ul care reprezintă procentul curent de încărcare clipeste, în timp ce LED-urile anterioare rămân aprinse continuu, iar celelalte sunt stinse.
</details>
<details>
<summary>3) Controlul Încărcării - Butonul Start</summary>
  
- Apăsare scurtă a butonului de Start: Declanșează procesul de încărcare.
- După apăsare, LED-ul RGB devine roșu pentru a indica că stația este ocupată.
- Încărcarea începe prin aprinderea și clipirea LED-ului L1, iar la fiecare 3 secunde se trece la următorul LED (L2, L3, L4).
- După finalizarea fiecărui pas de încărcare, LED-ul respectiv rămâne aprins, iar următorul începe să clipească.
- La finalizarea procesului (când L4 atinge 100%), toate LED-urile de încărcare vor clipi simultan de 3 ori, după care se vor stinge, semnalizând sfârșitul încărcării. LED-ul RGB va deveni verde pentru a indica că stația este din nou liberă.
- Apăsarea butonului Start în timpul încărcării: Nu are efect asupra procesului de încărcare.
</details>
<details>
<summary>4) Oprirea Forțată a Încărcării - Butonul Stop</summary>
  
- Apăsare lungă a butonului de Stop (minim 1 secunda): Oprește imediat procesul de încărcare și resetează stația la starea inițială.
- Indiferent de stadiul în care se află procesul de încărcare, apăsarea lungă a butonului de stop declanșează animația de final (toate LED-urile clipesc de 3 ori), iar LED-ul RGB revine la verde, indicând că stația este liberă.
- Apăsarea butonului Stop cât stația este liberă: Nu are efect.
</details>

## 1.2 Componentele utilizate
In realizarea montajului am utilizat urmatoarele componente:
- Breadboard
- 4x LED-uri albastre(pentru simularea procesului de incarcare)
- 1x LED RGB (pentru indicarea starii statiei(ocupata/libera))
- 2x butoane (1 buton de start si 1 buton de stop pentru incarcare)
- Un total de 9 rezistoare dintre care:
* 7 cu valoarea = 330 ohm
* 2 cu valoarea = 1K
- 14X fire pentru legaturi
- Placuta de Arduino UNO din kit-ul primit 
# 2)Cerinte:
<details> 
<summary>2.1 Detalii tehnice</summary>

Led-ul RGB reprezintă disponibilitatea stației. Dacă stația este liberă led-ul va fi verde, iar dacă stația este ocupată se va face roșu.

Led-urile simple reprezintă gradul de încărcare al bateriei, pe care îl vom simula printr-un loader progresiv (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%). Loader-ul se încărca prin aprinderea succesivă a led-urilor, la un interval fix de 3s. LED-ul care semnifică procentul curent de încărcare va avea starea de clipire, LED-urile din urma lui fiind aprinse continuu, iar celelalte stinse.

Apăsarea scurtă a butonului de start va porni încărcarea. Apăsarea acestui buton în timpul încărcării nu va face nimic.

Apăsarea lungă a butonului de stop va opri încărcarea forțat și va reseta stația la starea liberă. Apăsarea acestui buton cat timp stația este liberă nu va face nimic.
</details>
<details>
<summary> 2.2 Flow-ul procesului: </summary>
1) Stația începe în starea liberă, cu LED-ul RGB aprins verde și toate LED-urile de încărcare stinse.
  
2) După apăsarea scurtă a butonului de start, LED-ul RGB se face roșu, iar procesul de încărcare începe:
- LED-ul L1 clipeste timp de 3 secunde, apoi rămâne aprins.
- LED-ul L2 începe să clipească pentru a semnala încărcarea la 50%, iar L1 rămâne aprins.
- Procesul continuă în același mod pentru L3 (75%) și L4 (100%).
  
3) După finalizarea încărcării, toate LED-urile clipesc de 3 ori pentru a semnaliza finalizarea procesului, iar LED-ul RGB revine la verde.

4) Dacă în timpul încărcării este apăsat lung butonul de stop, încărcarea se întrerupe și LED-urile clipesc de 3 ori, iar LED-ul RGB devine verde, indicând că stația este din nou liberă.
</details>

# 3)Schema electrica:
![Screenshot 2024-10-20 173053](https://github.com/user-attachments/assets/d47b12ed-f245-4149-81c6-ed802e61a339)

# 4)Poze montaj fizic:
![Montaj_fizic1](https://github.com/user-attachments/assets/61013026-96f7-4ef9-9a7f-01c2601585f9)
![Montaj_fizic2](https://github.com/user-attachments/assets/ad737055-e14d-419b-90c5-dd8e44323375)
![Montaj_fizic3](https://github.com/user-attachments/assets/b1915015-1762-4a53-886d-e59cc22b882a)

# 5)Link video:
https://youtube.com/watch/-Os1j6454DM?feature=share
