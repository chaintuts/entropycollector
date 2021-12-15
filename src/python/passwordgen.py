# This code takes entropy stored by the accelerometer entropy collector and generates passwords
#
# Author: Josh McIntyre
#

import hashlib
from enum import Enum
import string
import base64

# Define constants
ENTROPY_FILE = "ENTROPY.TXT"
MAX_LENGTH = 86 # 512 bits encoded as base64 gives 86 ASCII characters
MIN_LENGTH = 8 # Far below a sane limit, but this is a demo. Some legacy systems hate their users.
MAX_PASSWORDS = 256 # Can request up to 256 passwords at a time
MIN_PASSWORDS = 1

# Read the entropy from the file and feed a hash
def hash_from_entropy():

    hasher = hashlib.sha512()

    with open(ENTROPY_FILE) as f:
        while True:
            
            # The file is written in hexadecimal text format, so read each byte as 2 hex characters
            chars = f.read(2)
            if not chars:
                break
            if not len(chars) == 2:
                break
            entropy_byte = bytes.fromhex(chars)

            # Update the hash state
            hasher.update(entropy_byte)

    # Get the final "seed"
    return hasher.digest()

# Generate the desired password(s)
def generate_passwords(seed, length=20, num_passwords=1):

    if length > MAX_LENGTH:
        print(f"Maximum password length is {MAX_LENGTH}")
    if length < MIN_LENGTH:
        print(f"Minimum password length is {MIN_LENGTH}")
    if num_passwords > MAX_LENGTH:
        print(f"Maximum number of passwords is {MAX_PASSWORDS}")
    if num_passwords < MIN_LENGTH:
        print(f"Minimum number of passwords is {MIN_PASSWORDS}")

    passwords = []
    for i in range(0, num_passwords):
        raw_bytes = hashlib.sha256(seed + i.to_bytes(1, 'big')).digest()
        encoded = base64.b64encode(raw_bytes, altchars=b'!#')
        full = encoded.decode().replace("=","")
        password = full[:length]
        passwords.append(password)

    return passwords


# The main entry point for the program
def main():

    # Get the seed from the entropy file
    seed = hash_from_entropy()

    # Print the seed in hex format
    print(f"Seed generated from entropy via SHA-512 (hex): {seed.hex()}")

    # Get the password(s)
    passwords = generate_passwords(seed, length=20, num_passwords=10)

    # Print the key
    print("Generated password(s):")
    for password in passwords:
        print(password)

if __name__ == "__main__":
    main()
