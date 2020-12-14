export type Maybe<T> = T | null;
export type Exact<T extends { [key: string]: unknown }> = { [K in keyof T]: T[K] };
export type MakeOptional<T, K extends keyof T> = Omit<T, K> & { [SubKey in K]?: Maybe<T[SubKey]> };
export type MakeMaybe<T, K extends keyof T> = Omit<T, K> & { [SubKey in K]: Maybe<T[SubKey]> };
/** All built-in and custom scalars, mapped to their actual values */
export type Scalars = {
  ID: string;
  String: string;
  Boolean: boolean;
  Int: number;
  Float: number;
};

export type Query = {
  __typename?: 'Query';
  wiki?: Maybe<Page>;
};


export type QueryWikiArgs = {
  path?: Maybe<Scalars['String']>;
};

export type Note = {
  __typename?: 'Note';
  name: Scalars['String'];
  title: Scalars['String'];
  text: Scalars['String'];
};

export type Page = {
  __typename?: 'Page';
  path: Scalars['String'];
  note: Note;
  notes?: Maybe<Array<Maybe<Page>>>;
};


export type PageNotesArgs = {
  depth?: Maybe<Scalars['Int']>;
};

export type Article = {
  path: Scalars['String'];
  title: Scalars['String'];
  text: Scalars['String'];
};
