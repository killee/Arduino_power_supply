Arduino_power_supply
====================

Arduino Controller laboratory power supply

Ich habe ein Netzteil mit einer Arduino Steuerung wieder aufgebaut. Hab das vor gut 10 Jahren in meiner Ausbildung gebaut. Leider habe ich irgendwann den C-Controll zerstört. Als ich mich über mein viel zu unpräzises Netzteil für zu Hause geärgert habe, dachte ich mir ich bau das wieder auf.

Dazu habe ich mit ein paar fertige Arduino Libs schnell das fertige Programm für den Arduino (bei mir einen Leonardo) zusammen geschrieben. Dafür ist Arduino echt super!

Der Arduino steuert mit PWM Ausgängen die Sollwerte des Analogteils des Netzteils. Hier greife ich auf eine Libary zu die einen simple Erhöhung der PWM Frequenz und Auflösung ermöglicht. Echt schön, kein gefrickel beim wechseln des Controllers ;-)!

Mit zwei ADC Eingängen bekomme ich die Ist Werte. Die ADCs übersample ich mit 12bit, die Referenzspannung schalte ich wenn möglich auf die interne um. Somit bekomme ich ganz brauchbare Werte.

Die Ausgabe erfolgt auf ein 4X20 Display. Dort werden Soll-, Ist Werte sowie Zusatzinfos dargestellt.

Die Eingabe erfolgt mit einer Matrix Tastatur. Werte werden direkt eingegeben und mit einer entsprechenden Taste für Spannung, Strom und Leistung direkt übernommen.

Ein Relais trennt die das Netzteil von den Klemmen um ständiges Ein- und Ausstecken zu vermeiden.

Die Genauigkeit liegt bei ca. 50mV und 5mA.

Über die USB-Serielle Schnittstelle gibt das Netzteil schon die Infos aus und empfängt Steuerbefehle.

Ich plane noch eine Ansteuerung über ein PC-Host Programm um auch vordefinierte Kurfen, Zyklen abfahren zu können. Hab mich da mal mit LabView versucht, aber bei mir ist das zu lange her und ich muss mich da wieder ganz neu ein arbeiten.

Das Projekt liegt auf GitHub ( https://github.com/killee/Arduino_power_supply ). Wollte mich da mal einarbeiten. Git gefällt mir bis jetzt echt gut ;-)!

Viele Grüße,
Kille
