#!/usr/bin/env python

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import pandas as pd
import socket

limit = 1000     # set sensor max output
frequency = 50
quiver = None
quiver2 = None
previous_vector = None
previous_vector2 = None
text_obj = None
text_obj4 = None

TCP_IP = '192.168.0.100'
TCP_PORT = 8085 


def sensorToVector(no_sensor):

    if no_sensor == 19:
        sensor_pos_vector[0] = -1
        sensor_pos_vector[1] = 0
        sensor_pos_vector[2] = 0
    if no_sensor == 1 or no_sensor == 8 or no_sensor == 16:
        sensor_pos_vector[0] = 0
        sensor_pos_vector[1] = 1
        sensor_pos_vector[2] = 0
    if no_sensor == 6 or no_sensor == 7 or no_sensor == 15 or no_sensor == 22 or no_sensor == 23:
        sensor_pos_vector[0] = 0
        sensor_pos_vector[1] = -1
        sensor_pos_vector[2] = 0
    if no_sensor == 17 or no_sensor == 18:
        sensor_pos_vector[0] = -1
        sensor_pos_vector[1] = 1
        sensor_pos_vector[2] = 0
    if no_sensor == 20 or no_sensor == 21:
        sensor_pos_vector[0] = -1
        sensor_pos_vector[1] = -1
        sensor_pos_vector[2] = 0
    
    if no_sensor == 11 or no_sensor == 12 or no_sensor == 13:
        sensor_pos_vector[0] = -1
        sensor_pos_vector[1] = 0
        sensor_pos_vector[2] = 1
    if no_sensor == 2:
        sensor_pos_vector[0] = 0
        sensor_pos_vector[1] = 1
        sensor_pos_vector[2] = 1
    if no_sensor == 5:
        sensor_pos_vector[0] = 0
        sensor_pos_vector[1] = -1
        sensor_pos_vector[2] = 1
    if no_sensor == 8 or no_sensor == 9 or no_sensor == 10:
        sensor_pos_vector[0] = -1
        sensor_pos_vector[1] = 1
        sensor_pos_vector[2] = 1
    if no_sensor == 14 or no_sensor == 15:
        sensor_pos_vector[0] = -1
        sensor_pos_vector[1] = -1
        sensor_pos_vector[2] = 1
    if no_sensor == 3 or no_sensor == 4:
        sensor_pos_vector[0] = 0
        sensor_pos_vector[1] = 0
        sensor_pos_vector[2] = 1



def main():

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((TCP_IP, TCP_PORT))
    server_socket.listen(1)
    print("Waiting for connections...")

    while True:

        client_socket, client_address = server_socket.accept()
        print("Connection accepted from:", client_address)

        client_socket.send(b"i")

        global sensor_pos_vector
        sensor_pos_vector = [0]*3

        fig = plt.figure()
        ax = plt.axes(projection='3d')
        ax.set_xlim([-100, 100])
        ax.set_ylim([-100, 100])
        ax.set_zlim([-100, 100])
        ax.view_init(25, 195)

        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')

        # Aggiunta della sfera
        r = 8  # Raggio della sfera
        phi, theta = np.mgrid[0.0:2.0 * np.pi:100j, 0.0:np.pi:50j]
        x = r * np.sin(theta) * np.cos(phi)
        y = r * np.sin(theta) * np.sin(phi)
        z = r * np.cos(theta)
        ax.plot_surface(x, y, z, color='black', alpha=0.8)

        start = [0, 0, 0]

        def update_plot(frame):

            data = client_socket.recv(1024)

            if not data:
                # Se non ci sono dati ricevuti, la connessione è stata interrotta
                print("Connection interrupted by:", client_address)

            message = data.decode()
            values = message.split(",")

            distance = int(values[0])
            signalStrenght = int(values[1])
            minSensorPosition = int(values[2])

            sensorToVector(minSensorPosition)
            sensor_pos_vector_final= [0] * 3
            sensor_pos_vector_final = [element*min(distance, 100) for element in sensor_pos_vector]

            current_vector = np.array(sensor_pos_vector_final)

            global previous_vector, quiver, text_obj, text_obj4

            text_position = (120, -130)  
            text_value = distance
            text_position2 = (165, -120)  
            text_value2 = 'Distance:'
            text_position3 = (75, -138)  
            text_value3 = 'Signal strength:'
            text_position4 = (35, -145)  
            text_value4 = signalStrenght
            
            if text_obj is None:
                text_obj = ax.text(text_position[0], text_position[1], ax.get_zlim()[1], str(text_value), ha='left', va='top')
                ax.text(text_position2[0], text_position2[1], ax.get_zlim()[1], str(text_value2), ha='left', va='top')
                ax.text(text_position3[0], text_position3[1], ax.get_zlim()[1], str(text_value3), ha='left', va='top', color='lightgray')
                text_obj4 = ax.text(text_position4[0], text_position4[1], ax.get_zlim()[1], str(text_value4) + '%', ha='left', va='top', color='lightgray')
            else:
                text_obj.set_text(str(text_value))
                text_obj4.set_text(str(text_value4) + '%')

            if previous_vector is not None and not np.array_equal(current_vector, previous_vector):
                # Rimuovi il vettore precedente dal grafico
                quiver.remove()

            if previous_vector is None or not np.array_equal(current_vector, previous_vector):
                # Aggiorna il vettore precedente con il nuovo vettore
                previous_vector = current_vector

                # Aggiungi il nuovo vettore al grafico
                quiver = ax.quiver(start[0], start[1], start[2], current_vector[0], current_vector[1], current_vector[2], color='red')

        anim = animation.FuncAnimation(fig, update_plot, cache_frame_data=False,  interval=frequency)

        plt.show()

        client_socket.close()
        break

    server_socket.close()


if __name__ == '__main__':
    main()
