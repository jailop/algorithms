#!/usr/bin/python

"""
Hasher
Produce hash representations for a list of usernames and pin codes.
List should be in CSV format with headers `user` and `pin`.
SHA-512 encryption algorithm is used for hash generation.
"""

import os
import sys
import json
import hashlib

EXT = ".json"

def load_list(path: str) -> list[dict]:
    """To load username/pin file list"""
    # Checking if the file exists
    if not os.path.exists(path):
        print("Error: File doesn't exist", file=sys.stderr)
        sys.exit(1)
    # Loading data from file
    with open(path, "r", encoding="utf-8") as fd:
        data = fd.readlines() 
    rows = []
    error = False
    first = True
    for num, line in enumerate(data):
        line = line.strip()
        if line[0] == "#" or line == "":
            continue
        tokens = line.strip().split(",")
        if len(tokens) != 2:
            print(f"Error: Invalid format at line {num}", file=sys.stderr)
            error = True
            continue
        if first:
            if tokens[0] != "user" or tokens[1] != "pin":
                print(f"Error: Invalid file header", file=sys.stderr)
                error = True
            first = False
            continue
        rows.append({"user": tokens[0], "pin": tokens[1]})
    if error:
        print("Hashing aborted", file=sys.stderr)
        sys.exit(1)
    return rows

def hash_text(text: str, salt: str) -> str:
    """To create a hash"""
    hasher = hashlib.sha512()
    plain = text + salt
    hasher.update(plain.encode())
    return hasher.hexdigest()

def create_hashes(records: list[dict], salt: str) -> list[dict]:
    """Convert user names and pines to hash representations"""
    return [
        [hash_text(item["user"], salt), hash_text(item["pin"], salt)]
        for item in records
    ]

def save_hashes(path: str, records: list[dict], salt: str) -> None:
    """To save the list of hashes"""
    with open(path, "w", encoding="utf-8") as fd:
        json.dump({
            "passphrase": os.environ["COOKIE_SECRET"],
            "records": records,
        }, fd)

def cli():
    """Terminal user interface"""
    if len(sys.argv) != 2: 
        print(f"Usage: {sys.argv[0]} USER_LIST_FILE")
        sys.exit(1)
    path = sys.argv[1]
    if not os.path.exists(path):
        print(f"File {path} does not exist")
        sys.exit(1)
    salt = ""
    if "COOKIE_SECRET" in os.environ:
        salt = os.environ["COOKIE_SECRET"]
    else:
        salt = input("Passphrase for encrypting:")
    print("Encrypting... ", end="")
    rows = load_list(path)
    rows = create_hashes(rows, salt)
    period_pos = path.rfind(".")
    if period_pos == -1:
        path += EXT
    elif path[period_pos:] == EXT:
        path += EXT
    else:
        segment = path[period_pos:]
        path = path.replace(segment, EXT)
    save_hashes(path, rows, salt)
    print("done.")
    print("Result was saved to", path)

if __name__ == "__main__":
    cli()
