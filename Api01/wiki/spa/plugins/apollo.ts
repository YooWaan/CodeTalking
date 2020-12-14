import { Plugin } from '@nuxt/types';
import { initializeApolloHelpers } from '~/apollo/accessor';

const accessor: Plugin = ({ app }) => {
  app.apolloProvider?.defaultClient &&
    initializeApolloHelpers(app.apolloProvider?.defaultClient);
};

export default accessor;
