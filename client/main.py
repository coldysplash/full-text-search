import ctypes
import argparse
import readline
import traceback
import logging
import os

# Загрузка библиотеки
fts_searcher_c = ctypes.CDLL("build/release/src/searcher-c/libsearcher-c.so")

# Определение типов данных
class Json(ctypes.Structure):
    pass

class IndexAccessor(ctypes.Structure):
    pass

class Results(ctypes.Structure):
    pass

# Определение аргументов и возвращаемых значений для функций
fts_searcher_c.fts_create_json.argtypes = [ctypes.c_char_p]
fts_searcher_c.fts_create_json.restype = ctypes.POINTER(Json)

fts_searcher_c.fts_delete_json.argtypes = [ctypes.POINTER(Json)]
fts_searcher_c.fts_delete_json.restype = None

fts_searcher_c.fts_create_searcher.argtypes = [ctypes.c_char_p, ctypes.POINTER(Json)]
fts_searcher_c.fts_create_searcher.restype = ctypes.POINTER(IndexAccessor)

fts_searcher_c.fts_delete_searcher.argtypes = [ctypes.POINTER(IndexAccessor)]
fts_searcher_c.fts_delete_searcher.restype = None

fts_searcher_c.fts_search.argtypes = [ctypes.c_char_p, ctypes.POINTER(IndexAccessor)]
fts_searcher_c.fts_search.restype = ctypes.POINTER(Results)

fts_searcher_c.fts_delete_results.argtypes = [ctypes.POINTER(Results)]
fts_searcher_c.fts_delete_results.restype = None

fts_searcher_c.fts_print_result.argtypes = [
    ctypes.POINTER(IndexAccessor),
    ctypes.POINTER(Results)
]
fts_searcher_c.fts_print_result.restype = None

class pyJson(ctypes.Structure):
    def __init__(self, json_path):
        self._pointer = fts_searcher_c.fts_create_json(json_path.encode("utf-8"))

    def __del__(self):
        fts_searcher_c.fts_delete_json(self._pointer)

class pyIndexAccessor(ctypes.Structure):
    def __init__(self, index_path, json):
        self._pointer = fts_searcher_c.fts_create_searcher(index_path.encode("utf-8"), json)

    def __del__(self):
        fts_searcher_c.fts_delete_searcher(self._pointer)

class pyResults(ctypes.Structure):
    def __init__(self, query, accessor):
        self._pointer = fts_searcher_c.fts_search(query.encode("utf-8"), accessor)

    def __del__(self):
        fts_searcher_c.fts_delete_results(self._pointer)

# Парсим аргументы
parser = argparse.ArgumentParser(description='Search query in index')
parser.add_argument("--index", type=str, required=True, help="path to index")
parser.add_argument("--query", type=str, required=False, help="query for search")
args = parser.parse_args()

if (args.index == 0):
    input("Invalid name for index")

json_path = "config.json"
json = pyJson(json_path)
clear = lambda: os.system('clear')

if (args.query):
    clear()
    try:
        accessor = pyIndexAccessor(args.index, json._pointer)
        results = pyResults(args.query, accessor._pointer)
        fts_searcher_c.fts_print_result(accessor._pointer, results._pointer)
    except Exception as e:
        logging.error(traceback.format_exc())
else:
    while(True):
        query = input("Enter query: ")
        clear()
        try:
            accessor = pyIndexAccessor(args.index, json._pointer)
            results = pyResults(query, accessor._pointer)
            fts_searcher_c.fts_print_result(accessor._pointer, results._pointer)
        except Exception as e:
            logging.error(traceback.format_exc())