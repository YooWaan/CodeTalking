package ql

// This file will be automatically regenerated based on the schema, any resolver implementations
// will be copied through when generating and any unknown code will be moved to the end.

import (
	"context"
)

func (r *pageResolver) Notes(ctx context.Context, obj *Page, depth *int) ([]*Page, error) {
	return Tree(ctx, obj, depth), nil
}

// Page returns PageResolver implementation.
func (r *Resolver) Page() PageResolver { return &pageResolver{r} }

type pageResolver struct{ *Resolver }
