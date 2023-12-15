#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ParserOpts ParserOpts;
typedef struct SearcherHandle SearcherHandle;
typedef struct Results Results;

ParserOpts *fts_create_json(const char *path);

void fts_delete_json(ParserOpts *config);

SearcherHandle *fts_create_searcher(const char *path, ParserOpts *config);

void fts_delete_searcher(SearcherHandle *handle);

Results *fts_search(const char *query, const SearcherHandle *handle);

void fts_print_result(const SearcherHandle *handle, const Results *result);

void fts_delete_results(Results *result);

#ifdef __cplusplus
}
#endif
