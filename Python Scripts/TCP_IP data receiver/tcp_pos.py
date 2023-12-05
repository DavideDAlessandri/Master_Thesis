import socket

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

    while True:
        # Ricevi i dati dal client
        data = client_socket.recv(1024)
        
        if not data:
            # Se non ci sono dati ricevuti, la connessione è stata interrotta
            print("Connessione interrotta da:", client_address)
            break

        # Decodifica e stampa i dati ricevuti
        message = data.decode()
        #values = message.split(",")

        #distance = int(values[0])
        #signalStrenght = int(values[1])
        #minSensorPosition = int(values[2])

        print(message)

    # Chiudi la connessione con il client
    client_socket.close()
    break

# Chiudi il socket del server
server_socket.close()
