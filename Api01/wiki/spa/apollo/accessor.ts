import { ApolloClient } from 'apollo-client'

let $apolloClient: ApolloClient<any>;

export function initializeApolloHelpers(apolloClient: ApolloClient<any>) {
  $apolloClient = apolloClient;
  $apolloClient.defaultOptions = {
    query: {
      fetchPolicy: 'no-cache',
    }
  }
}

export { $apolloClient };
