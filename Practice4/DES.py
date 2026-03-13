import base64
import random
import string
import secrets
from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad


def generate_key(length=8):
    alphabet = string.printable
    key = ""
    for i in range(length):
        key += alphabet[secrets.randbelow(len(alphabet))]

    print("Clave generada en binario: ", end="")
    key_binary = key.encode()
    for byte in key_binary:
        print(f"{byte:08b}", end="")

    print("\nClave en bytes: ", end="")
    print(key_binary)

    key_b64 = encode_to_base64(key)
    print(f"\nClave codificada en base 64: {key_b64}")

    return key_binary


def encode_to_base64(datos):
    if type(datos) == bytes:
        resultado_binary = datos
    else:
        resultado_binary = datos.encode()

    resultado_b64 = base64.b64encode(resultado_binary)
    return resultado_b64.decode()  


def decode_from_base64(datos_b64):
    if type(datos_b64) == bytes:
        base64_bytes = datos_b64
    else:
        base64_bytes = datos_b64.encode()

    resultado_binary = base64.b64decode(base64_bytes)
    return resultado_binary


def cipher_file(filename, key):
    cipher = DES.new(key, DES.MODE_ECB)

    # Abrir el archivo en modo binari0 y leer su contenido en BYTES
    with open(filename, "rb") as f:
        plaintext = f.read()

    # DES solo cifra bloques de 8 bytes, por lo que es necesario rellenar el texto plano para que su longitud sea un múltiplo de 8
    cifrado = cipher.encrypt(pad(plaintext, DES.block_size))

    # Convertir el cifrado a Base64
    cifrado_b64 = encode_to_base64(cifrado)

    salida = "Ciphertext_" + filename
    with open(salida, "w") as f:
        f.write(cifrado_b64)


    return salida


def decipher_file(filename, key):
    cipher = DES.new(key, DES.MODE_ECB)

    with open(filename, "rb") as f:
        ciphertext_b64 = f.read()

    ciphertext = decode_from_base64(ciphertext_b64)
    datos = unpad(cipher.decrypt(ciphertext), DES.block_size)

    salida = "Plaintext_" + filename
    with open(salida, "wb") as f:
        f.write(datos)

    return salida



def main():
    
    match input("Elija una opción:\n1. Generar clave\n2. Cifrar un archivo\n3. Descifrar un archivo\n"):
        case "1":
            generate_key()
        case "2":
            key_b64 = input("Ingrese la clave en Base64: ")
            key = decode_from_base64(key_b64)
            archivo_cifrado = cipher_file("mensaje.txt", key)
            print("Cifrado en:", archivo_cifrado)
        case "3":
            key_b64 = input("Ingrese la clave en Base64: ")
            key = decode_from_base64(key_b64)
            archivo_descifrado = decipher_file("Ciphertext_mensaje.txt", key)
            print("Descifrado en:", archivo_descifrado)
        case _:
            print("Opción no válida")
    
    
if __name__ == "__main__":
    main()




