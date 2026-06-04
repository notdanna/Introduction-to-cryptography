from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util import Counter
import base64

# Section 1: Learning how to use AES in CTR mode
# Exercise 1:
def generate_aes_key(bits):
    if bits not in (128, 192, 256):
        raise ValueError("AES solo acepta 128, 192 o 256 bits.")
    return get_random_bytes(bits // 8)

# Exercise 2:
def encrypt_aes_ctr(plaintext, key):
    nonce = get_random_bytes(8)
    ctr = Counter.new(64, prefix=nonce, initial_value=0)
    cipher = AES.new(key, AES.MODE_CTR, counter=ctr)
    ciphertext = cipher.encrypt(plaintext)
    return nonce, ciphertext

# Exercise 3:
def decrypt_aes_ctr(ciphertext, key, nonce):
    ctr = Counter.new(64, prefix=nonce, initial_value=0)
    cipher = AES.new(key, AES.MODE_CTR, counter=ctr)
    return cipher.decrypt(ciphertext)



# Section 2: Using AES properly
# Exercise 1: 
def save_key(key, filename):
    with open(filename, "w") as f:
        f.write(base64.b64encode(key).decode())

# Exercise 2:
def load_key(filename):
    with open(filename, "r") as f:
        key_b64 = f.read().strip()
    return base64.b64decode(key_b64)

def encrypt_file_aes_ctr(plaintext_filename, key_filename, output_filename):
    key = load_key(key_filename)

    with open(plaintext_filename, "rb") as f:
        plaintext = f.read()

    nonce = get_random_bytes(8)
    ctr = Counter.new(64, prefix=nonce, initial_value=0)
    cipher = AES.new(key, AES.MODE_CTR, counter=ctr)
    ciphertext = cipher.encrypt(plaintext)

    nonce_b64 = base64.b64encode(nonce).decode()
    ciphertext_b64 = base64.b64encode(ciphertext).decode()

    with open(output_filename, "w") as f:
        f.write(nonce_b64 + "\n")
        f.write(ciphertext_b64)

    print("Nonce (Base64):", nonce_b64)
    print("Ciphertext guardado en:", output_filename)

# Exercise 3:
def decrypt_file_aes_ctr(ciphertext_filename, key_filename, output_filename):
    key = load_key(key_filename)

    with open(ciphertext_filename, "r") as f:
        nonce_b64 = f.readline().strip()
        ciphertext_b64 = f.readline().strip()

    nonce = base64.b64decode(nonce_b64)
    ciphertext = base64.b64decode(ciphertext_b64)

    plaintext = decrypt_aes_ctr(ciphertext, key, nonce)

    with open(output_filename, "wb") as f:
        f.write(plaintext)

    print("Plaintext recuperado guardado en:", output_filename)




if __name__ == "__main__":
    while True:
        print("\n1. Seccion 1")
        print("2. Seccion 2")
        print("3. Salir")

        main_option = input("Opcion: ")

        if main_option == "1":
            while True:
                print("\n--- Seccion 1 ---")
                print("1. Generar llave")
                print("2. Cifrar")
                print("3. Descifrar")
                print("4. Regresar")

                option = input("Opcion: ")

                if option == "1":
                    bits = int(input("Bits (128, 192, 256): "))
                    key = generate_aes_key(bits)
                    print("Key (Base64):", base64.b64encode(key).decode())

                elif option == "2":
                    key_b64 = input("Dame la key en Base64: ")
                    message = input("Dame el mensaje a cifrar: ")

                    key = base64.b64decode(key_b64)
                    plaintext = message.encode("utf-8")

                    nonce, ciphertext = encrypt_aes_ctr(plaintext, key)

                    print("Nonce (Base64):", base64.b64encode(nonce).decode())
                    print("Ciphertext (Base64):", base64.b64encode(ciphertext).decode())

                elif option == "3":
                    key_b64 = input("Dame la key en Base64: ")
                    nonce_b64 = input("Dame el nonce en Base64: ")
                    ciphertext_b64 = input("Dame el ciphertext en Base64: ")

                    key = base64.b64decode(key_b64)
                    nonce = base64.b64decode(nonce_b64)
                    ciphertext = base64.b64decode(ciphertext_b64)

                    plaintext = decrypt_aes_ctr(ciphertext, key, nonce)
                    print("Texto recuperado:", plaintext.decode("utf-8"))

                elif option == "4":
                    break

                else:
                    print("Opcion invalida.")

        elif main_option == "2":
            while True:
                print("\n--- Seccion 2 ---")
                print("1. Generar llave y guardarla en archivo")
                print("2. Cifrar archivo con AES-CTR")
                print("3. Descifrar archivo con AES-CTR")
                print("4. Regresar")

                option = input("Opcion: ")

                if option == "1":
                    bits = int(input("Bits (128, 192, 256): "))
                    filename = input("Nombre del archivo para guardar la llave: ")

                    key = generate_aes_key(bits)
                    save_key(key, filename)

                    print("Key (Base64):", base64.b64encode(key).decode())
                    print("Llave guardada en:", filename)

                elif option == "2":
                    key_filename = input("Dame el nombre del archivo donde esta la key: ")
                    plaintext_filename = input("Dame el nombre del archivo plaintext: ")
                    output_filename = input("Dame el nombre del archivo de salida del ciphertext: ")

                    encrypt_file_aes_ctr(plaintext_filename, key_filename, output_filename)

                elif option == "3":
                    key_filename = input("Dame el nombre del archivo donde esta la key: ")
                    ciphertext_filename = input("Dame el nombre del archivo del ciphertext: ")
                    output_filename = input("Dame el nombre del archivo para guardar el plaintext recuperado: ")

                    decrypt_file_aes_ctr(ciphertext_filename, key_filename, output_filename)

                elif option == "4":
                    break

                else:
                    print("Opcion invalida.")

        elif main_option == "3":
            print("Salir")
            break