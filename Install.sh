#! /bin/bash

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    echo "Error: This script must be sourced." >&2
    echo "Usage: source $0" >&2
    return 1
fi

WorkDir=$(pwd)

if [[ -d "${WorkDir}/Nuclear_Techniques_pyenv" ]]; then
    read -r -p "Pyenv folder already seems to exist. Continue anyway? (y/N): " choice
    case "$choice" in
        [yY][eE][sS]|[yY])
            echo "Proceeding anyway..."
	    module load ROOT/6.40.02-foss-2025b
	    python3 -m venv "${WorkDir}/Nuclear_Techniques_pyenv"
	    source ${WorkDir}/Nuclear_Techniques_pyenv/bin/activate
	    pip3 install notebook metakernel
	    echo ""
	    echo ""
	    echo"Environment setup successful, you can now load the notebooks and run the lessons"
            ;;
        *)
            echo "Aborted. Source the SetEnv.sh script instead if you previously set the environment up."
            return 2
            ;;
    esac
else
    module load ROOT/6.40.02-foss-2025b
    python3 -m venv "${WorkDir}/Nuclear_Techniques_pyenv"
    source ${WorkDir}/Nuclear_Techniques_pyenv/bin/activate
    pip3 install notebook metakernel
    echo ""
    echo ""
    echo "Environment setup successful, you can now load the notebooks and run the lessons."
    echo "Note, next time you can just do source SetEnv.sh."
fi

return 0;
