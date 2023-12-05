import socket
import time
import logging

log = False     # enable log data
if log:
    logging.basicConfig(filename='value.log', level=logging.INFO, format='%(message)s')
    name_array = "Delta time"
    logging.info(name_array)  # to log output values

# Configura l'indirizzo IP e la porta del server
TCP_IP = '192.168.0.100'  # Indirizzo IP del server
TCP_PORT = 8075     # Porta del server

# Crea un socket TCP/IP
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Collega il socket all'indirizzo IP e alla porta specificati
server_socket.bind((TCP_IP, TCP_PORT))

# Avvia l'ascolto del socket
server_socket.listen(1)

print("In attesa di connessioni...")

while True:
    # Accetta una connessione dal client
    client_socket, client_address = server_socket.accept()
    print("Connessione accettata da:", client_address)

    client_socket.send(b"i")

    previous_message_time = None  # Inizializza il tempo del messaggio precedente

    while True:
        # Ricevi i dati dal client
        data = client_socket.recv(1024)
        
        if not data:
            # Se non ci sono dati ricevuti, la connessione è stata interrotta
            print("Connessione interrotta da:", client_address)
            break

        # Registra il tempo di arrivo del messaggio
        current_time = time.time()
        message = data.decode()

        if previous_message_time is not None:
            time_difference = current_time - previous_message_time
            print("Tempo trascorso dal messaggio precedente: {:.2f} secondi".format(time_difference))
            logging.info(time_difference)

        previous_message_time = current_time

        # Decodifica e stampa i dati ricevuti
        # print(message)

    # Chiudi la connessione con il client
    client_socket.close()
    break

# Chiudi il socket del server
server_socket.close()
