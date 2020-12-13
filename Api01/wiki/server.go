package main

import (
	"log"
	"net/http"
	"os"
	"context"

	"github.com/99designs/gqlgen/graphql/handler"
	"github.com/99designs/gqlgen/graphql/playground"

	"note.mem/wiki/ql"
)

const defaultPort = "8080"

func main() {
	port := os.Getenv("PORT")
	if port == "" {
		port = defaultPort
	}

	ctx := ql.WithBook(context.Background())
	srv := handler.NewDefaultServer(ql.NewExecutableSchema(ql.Config{Resolvers: &ql.Resolver{}}))

	http.Handle("/", playground.Handler("GraphQL playground", "/query"))
	http.HandleFunc("/query", func(w http.ResponseWriter, r *http.Request) {
		srv.ServeHTTP(w, r.WithContext(ctx))
	})

	log.Printf("connect to http://localhost:%s/ for GraphQL playground", port)
	log.Fatal(http.ListenAndServe(":"+port, nil))
}
