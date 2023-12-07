#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Json Json;
typedef struct SearcherHandle SearcherHandle;
typedef struct Results Results;

Json *fts_create_json(const char *path);

void fts_delete_json(Json *config);

SearcherHandle *fts_create_searcher(const char *path, Json *config);

void fts_delete_searcher(SearcherHandle *handle);

Results *fts_search(const char *query, const SearcherHandle *handle);

void fts_print_result(const SearcherHandle *handle, const Results *result);

void fts_delete_results(Results *result);

#ifdef __cplusplus
}
#endif
