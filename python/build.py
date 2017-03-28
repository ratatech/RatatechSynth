import os


cmnd = 'eclipse --launcher.suppressErrors -nosplash -data "/home/rata/Projects/Eclipse Workspace/" -application org.eclipse.cdt.managedbuilder.core.headlessbuild -cleanBuild "RatatechSynth/Release"'
os.system(cmnd)