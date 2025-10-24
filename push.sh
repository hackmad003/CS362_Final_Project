#!/bin/bash

# Exit the script whenever a non-zero exit status is received
set -e

# Add the fold to commit
git add pthom29FinalProject

# Commit
git commit -m "Update pthom29FinalProject"

# Push
git push

