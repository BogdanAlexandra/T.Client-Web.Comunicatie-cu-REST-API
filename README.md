# Tema 4 - Client Web. Comunicaţie cu REST API
### - Protocoale de Comunicație -

   > STUDENT: Bogdan Alexandra-Lăcrămioara
   > GRUPA: 325CD

**Comenzi**

1. "register"
* citește username-ul și parola 
* verifică validitatea datelor: sunt empty sau conțion spațiu, afișând mesaje sugestive și nu se execută comanda în caz ca nu sunt valide
* răspunsurile serverului pot fi:
    * cont creat  : Se afișează mesajul "200 - OK - User registered successfully."
    * username indisponibil : Se afisează mesajul "400 - Bad Request - Username indisponibil!"

2. "login"
* citește username-ul și parola 
* verifică validitatea datelor: sunt empty sau conțion spațiu, afișând mesaje sugestive și nu se execută comanda, in caz ca nu sunt valide 
* răspunsurile de la server pot fi:
    * cont care nu este înregistrat : Se afișează mesajul "Error! No account with this username!"
    * credentialele nu corespund : Se afișează mesajul "Error! Credentials are not good!"
    * cont logat : Se afișează mesajul "200 - OK - Bun venit!"

3. "enter_library"
* răspunsurile de la server pot fi:
    * bibliotecă accesată 
    * bibllioteca nu poate fi accesată, deoarece utilizatorul nu este logat: Se afișează mesajul "Error! You are not logged in"
    

4. "get_books"
* se verifică dacă utilizatorul este logat, în caz contrar se afișează "Error! You don't have access to the library."
* răspunsurile de la server pot fi:
    * afișează cărțile
    * nu este dovedit accesul în librărie: Se afișează mesajul "Error! Something bad happened!"
* În cazul în care lista e cărți este goală se afișează: "There are no books!"

5. "get_book"
* se verifică dacă utilizatorul este logat, în caz contrar se afișează "Error! You don't have access to the library."
* citește id-ul
* verifică daca este număr sau contine spatiu si intoarce un mesaj sugestiv și nu se execută comanda in caz ca nu este valid 
* în caz contrar:
     *  răspunsurile serverului pot fi:
         * afișează cartea
         * id-ul nu există: Se afișează mesajul "Please try another id, because this is not found or is invalid"

6. "add_book"
* se citesc datele cărții
* se verifică validitatea lor și se afișează mesaje corespunzătoare și nu se execută comanda in caz ca nu sunt valide 
*  răspunsurile serverului pot fi:
    *  bad request: Se afișează mesajul "Error! Something bad happened!"
     * carte adăugată: Se afișează mesajul "The book was added".

7. "delete_book"
* se verifică dacă utilizatorul este logat, în caz contrar se afișează "Error! You don't have access to the library."
* citește id-ul
* verifică daca este număr sau contine spatiu si intoarce un mesaj sugestiv și nu se execută comanda în caz că nu este valid 
* răspunsurile serverului pot fi:
   * id-ul nu există: Se afișează mesajul "Please try another id, because this is not found or is invalid"
   * cartea este stearsa: se afiseaza mesajul "Book deleted."
   * bad request: se afisează mesajul "Error! Something bad happened!"

8. "logout"
* se verifica ca utilizatorul sa fie logat, in caz contrar se afiseaza ""Error! You are not logged in!"
* da logout la client: se afiseaza mesajul "Logout with success."
* eroare, deoarece utilizatorul nu este logat : se afiseaza mesajul "Error! Please login in first!"

9. "exit"
* închide clientul și afișează mesajul "Good bye!"


**Librăria de Parsare JSON**

Pentru a parsa răspunsurile primite de la server am ales biblioteca nlohmann::json, deoarece este ușor de utilizat pentru citirea, scrierea și manipularea datelor JSON în C++. 

**Funcții auxiliare folosite**

* **extract_cookies:** Această functie este folosită pentru a extrage cookie-urile din răpunsul serverului, folosite pentru autorizare.
* **digit:** Această funcție primește un șir de caractere și returnează true dacă acesta conține cel puțin o cifră și false în caz contrar. Este folosită pentru validarea datelor.
* **isspace:**  Această funcție primește un șir de caractere și returnează true dacă acesta conține cel puțin un spațiu și false în caz contrar. Este folosită pentru validarea datelor.
* **digits:** Această funcție primește un șir de caractere și returnează true dacă acesta conține doar cifre și false în caz contrar. Este folosită pentru validarea datelor.
* **receive_json:** Această funcție primește raspunsul ca un șir de caractere si returnează o instanță de tipul nlohmann::json care conține obiectul găsit. Este folosit pentru comanda get_books, pentru afișarea cărților.
* **receive_json_one_book:** Această funcție primește raspunsul ca șir de caractere și dacă găsește obiectul JSON, funcția va returna o instanță de tipul nlohmann::json care conține obiectul găsit. Este folosit pentru comanda get_book, la afișarea cărții cu id-ul cerut.

**Schelet**
* Tema mea are ca schelet laboratorul 9. În cadrul laboratorului am implementat doar request-uri de tip POST și GET. Ulterior, în realizarea temei am avut nevoie să trimit un request de tip DELETE, așadar am implementat funcția **compute_delete_request** .

**Testare server**
* Pentru a interacţiona neprogramatic cu serverul, am folosit utilitarul ce simulează clienţii HTTP, INSOMNIA.

**Păreri**
 * În opinia mea, această tema a fost binevenită în înțelegerea protocolului HTTP. Personal, această temă mi s-a părut foarte drăguță. Am ales limbajul C++, deoarece mi s-a părut mult mai ușor de lucrat cu librăria de parsare JSON, folosind-o anterior și la altă temă.

 **Reguli de rulare**
 * make : compileaza sursele
 * make run : construiește executabilul client (dacă este necesar) și îl   rulează folosind ./client.
 * make clean : șterge toate fișierele obiect (*.o) și executabilul client din director.
