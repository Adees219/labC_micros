from Adafruit_IO import Client
import time
import serial

ADAFRUIT_IO_KEY = 'aio_IplY97lvp8AhVctCwSNqpmGE7DEq'

ADAFRUIT_IO_USERNAME = 'Adees'

aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY) #conectar con el usuario de adafruit
ser = serial.Serial('COM3', 9600)
total = 0

#postlab
while True:
    cant = 0
    data = aio.receive('msg')
    valor = int(data.value)

    if (valor == 1):
        if ser: #Revisamos si hay conexión serial
            message = b"1" #Codificamos en bytes el dato que mandaremos al pic
            ser.write(message) #Le escribimos el dato el puerto serial 
        
    elif (valor == 0):
        if ser: #Revisamos si hay conexión serial
            message = b"0" #Codificamos en bytes el dato que mandaremos al pic
            ser.write(message) #Le escribimos el dato el puerto serial\
   
    if ser and ser.in_waiting>0:
        datoR = ser.read().decode().strip() 
        if datoR == 'Q':
            total += 1
            aio.send('cont1', total)  
    
    if cant == 255:
        cant = 0

    time.sleep(1)


#lab

# valor = 0
# while True:
    
#     data = aio.receive('msg')
#     temp = int(data.value)
#     if (temp == 1):
#         print('Modo reposo activado')
        
#     elif (temp == 0):
#         print('Modo reposo desactivado') 
#         valor += 1

#     aio.send('cont1', valor)

#     if valor == 255:
#         valor = 0

#     time.sleep(1)

