import base64



def encode_to_base64(datos_binarios):
 
    # Dato de entrada 
    print(datos_binarios)

    # Dato binario
    for byte in datos_binarios:
        print(chr(byte), end=" ")  
        print(f"{byte:08b}", end=" ")

    # Codificación
    resultado_b64 = base64.b64encode(datos_binarios)

    # El resultado es un objeto de bytes
    print(resultado_b64.decode('utf-8'))



def decode_from_base64(datos_b64):
 
    # Dato de entrada 
    print(b{datos_b64})


    # Dato b64
    for byte in datos_b64:
        print(f"{byte:08b}", end=" ")

    # Decodificación a binario
    resultado_binary = base64.b64decode(datos_b64)

    # El resultado es un String
    print(f"\n{resultado_binary}")


# Definicion como función main
if __name__ == "__main__":
   # encode_to_base64(b"Hola Mundo")
    decode_from_base64("SG9sYSBNdW5kbw==")