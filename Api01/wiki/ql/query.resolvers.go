package ql

// This file will be automatically regenerated based on the schema, any resolver implementations
// will be copied through when generating and any unknown code will be moved to the end.

import (
	"context"
)

func (r *queryResolver) Wiki(ctx context.Context, path *string) (*Page, error) {
	searchPath := "/"
	if path != nil {
		searchPath = *path
	}
	return Search(ctx, searchPath), nil
}

// Query returns QueryResolver implementation.
func (r *Resolver) Query() QueryResolver { return &queryResolver{r} }

type queryResolver struct{ *Resolver }
