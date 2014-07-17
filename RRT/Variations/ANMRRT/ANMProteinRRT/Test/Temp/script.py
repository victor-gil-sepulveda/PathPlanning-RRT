from schrodinger import maestro
from schrodinger import project
import schrodinger.graphics3d.common as common
import schrodinger.graphics3d.arrow as arrow


## Add two entries to the project table

primitives_grp = common.Group()


def deleteArrows():
	# Remove the markers and the callback.
	primitives_grp.clear()
	maestro.workspace_draw_function_remove(primitives_grp.draw)
	return

def prepareProjectTable(file1,file2):
	maestro.command("entryimport  format=pdb") 
	maestro.command('entryimport "%s"'%file1)#"/home/victor/workspace/C++2/PELE-1.5/src/PathPlanning/RRT/Variations/ANMRRT/ANMProteinRRT/Test/Temp/post_anm.pdb"')
	maestro.command('entryimport "%s"'%file2)#"/home/victor/workspace/C++2/PELE-1.5/src/Molecules/Test/Data/ProteinResiduesSamples/plop_ala.pdb"')
	maestro.command('showpanel table')
	maestro.command('entrywsinclude entry "1"')
	return

def drawArrows():
	pt = maestro.project_table_get()
	c_alpha_atoms =[]
	for row in pt.all_rows:
		st = row.getStructure()
		for atom in st.atom:
			if('CA' in atom.pdbname):
				c_alpha_atoms.append(atom)				
				print atom.x, atom.y, atom.z
	for i in range(len(c_alpha_atoms)/2):
		ar = arrow.Arrow(
			xhead=c_alpha_atoms[i].x, yhead=c_alpha_atoms[i].y, zhead=c_alpha_atoms[i].z,
			xtail=c_alpha_atoms[i +len(c_alpha_atoms)/2].x, ytail=c_alpha_atoms[i+len(c_alpha_atoms)/2].y, ztail=c_alpha_atoms[i+len(c_alpha_atoms)/2].z,
			color='red',
			radius=0.05,
			opacity=0.8,
			resolution=10)
		primitives_grp.add(ar)
	try:
		#maestro.workspace_draw_function_remove(primitives_grp.draw)			
		maestro.workspace_draw_function_add(primitives_grp.draw)
		
	except:
		print "function already registered"
	
	pt.update()

	return
