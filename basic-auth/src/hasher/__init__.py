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

def hash_text(text: str) -> str:
    """To create a hash"""
    salt = os.environ["COOKIE_SECRET"]
    hasher = hashlib.sha512()
    plain = text + salt
    hasher.update(plain.encode())
    return hasher.hexdigest()

def create_hashes(records: list[dict]) -> list[dict]:
    """Convert user names and pines to hash representations"""
    return [
        [hash_text(item["user"]), hash_text(item["pin"])]
        for item in records
    ]

def save_hashes(path: str, records: list[dict]) -> None:
    """To save the list of hashes"""
    with open(path, "w", encoding="utf-8") as fd:
        json.dump(records, fd)

if __name__ == "__main__":
    if "COOKIE_SECRET" not in os.environ:
        print("Set your secret word in the environment varable COOKIE_SECRET")
        sys.exit(1)
    path = sys.argv[1]
    rows = load_list(path)
    rows = create_hashes(rows)
    path = path.replace(".txt", ".json")
    save_hashes(path, rows)
