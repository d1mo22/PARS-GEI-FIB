#! /usr/bin/bash
#
# Make sure plugins/plugins.pro points to plugins/plugins-est.pro, then use:
# 
# first go to repository's root:
cd $(git rev-parse --show-toplevel)
if (ls -l plugins/plugins.pro | grep -E -- '-> plugins-est.pro$' > /dev/null)
  then
    git archive --format tgz --worktree-attributes \
      --prefix NewViewer_$(git log -1 --pretty=format:%h HEAD)/plugins/ \
      --add-file=plugins/plugins.pro  \
      --output ../NewViewer_$(git log -1 --pretty=format:%h HEAD).tgz \
      --prefix NewViewer_$(git log -1 --pretty=format:%h HEAD)/ HEAD
  else
    echo "Make sure plugins/plugins.pro points to plugins/plugins-est.pro,"
    echo "then re-run this."
fi
