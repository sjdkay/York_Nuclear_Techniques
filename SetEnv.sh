#! /bin/bash

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    echo "Error: This script must be sourced." >&2
    echo "Usage: source $0" >&2
    return 1
fi

WorkDir=$(pwd)
module load ROOT/6.40.02-foss-2025b
source ${WorkDir}/Nuclear_Techniques_pyenv/bin/activate

echo "Environment set. You can now run the notebooks."
echo "Consider adding the commands above to your bashrc file :)"

return 0;
