#include "GUIMcaLang.h"
#include <sstream>
#include <vector>
#include <osd_config.h>


CGUIMcaLang::CGUIMcaLang(void)
{
	for (std::map<const std::string, const std::string>::const_iterator i = m_default_lang.begin(); i != m_default_lang.end(); i++)
	{
		m_curr_lang.insert(*i);
	}
	//std::map<const std::string, const std::string>::iterator ilang;
	//if ( (ilang = m_curr_lang.find("LNG_PHRASE_ETC")) != m_curr_lang.end() )
	//but here easier to use: m_curr_lang["LNG_PHRASE_ETC"];
}

void CGUIMcaLang::trimLeft(std::string& str, const char* chars2remove)
{
	if (!str.empty())
	{
		std::string::size_type pos = str.find_first_not_of(chars2remove);

		if (pos != std::string::npos)
			str.erase(0,pos);
		else
			str.erase( str.begin() , str.end() ); // make empty
	}
}

void CGUIMcaLang::trimRight(std::string& str, const char* chars2remove)
{
	if (!str.empty())
	{
		std::string::size_type pos = str.find_last_not_of(chars2remove);

		if (pos != std::string::npos)
			str.erase(pos+1);
		else
			str.erase( str.begin() , str.end() ); // make empty
	}
}
//#define sio_printf printf
void CGUIMcaLang::initLang(std::string input)
{
	replace(&input, "\r\n", "\n");
	replace(&input, "\r", "\n");
	std::istringstream instream(input);
	std::string line;
	std::vector<std::string> all_lines;

	while(std::getline(instream, line, '\n'))
	{
		trimLeft(line, " ");
		trimRight(line, " ");
		if (line.empty()) continue;
		if (line[0] == '#' || (line[0] == '/' && line[1] == '/')) continue;
		if (line.find("=") == std::string::npos) continue;

		all_lines.push_back(line);
		//sio_printf("%s\n", line.c_str());
	}

	std::string::size_type subpos;
	std::string::size_type laspos;
	for (std::map<const std::string, const std::string>::const_iterator i = m_default_lang.begin(); i != m_default_lang.end(); i++)
	{
		for (u32 li = 0; li < all_lines.size(); li++)
		{
			subpos = all_lines[li].find((*i).first);
			if (subpos != std::string::npos)
			{
				if (all_lines[li][subpos+(*i).first.length()] == ' ' || all_lines[li][subpos+(*i).first.length()] == '=')
				{
					subpos = all_lines[li].find("\"");
					laspos = all_lines[li].rfind("\"");
					if (subpos != laspos)
					{
						m_curr_lang[(*i).first] = all_lines[li].substr(subpos+1, (laspos)-(subpos+1));
						replace(&m_curr_lang[(*i).first], "\\\"", "\"");
						replace(&m_curr_lang[(*i).first], "\\n", "\n");
						//sio_printf("Def repl: %s=%s\n", (*i).first.c_str(), m_curr_lang[(*i).first].c_str());
					}
				}
			}
		}
	}

	all_lines.clear();
}

CGUIMcaLang::~CGUIMcaLang(void)
{
	m_curr_lang.clear();
}

const char *CGUIMcaLang::getText(const char *label)
{
	return m_curr_lang[label].c_str();
}

void CGUIMcaLang::replace(std::string *base, const std::string find, const std::string repl)
{
	int lenrepl = repl.length();
	int lenfind = find.length();

	u32 i = 0;
	while ( std::string::npos != (i = base->find(find, i)) )
	{
		base->replace( i, lenfind, repl);
		i += lenrepl;
	}
}

void CGUIMcaLang::replace(std::string *base, const std::string find, const long long repln)
{
	std::ostringstream conv;

	conv << repln;
	std::string repl = conv.str();

	int lenrepl = repl.length();
	int lenfind = find.length();

	u32 i = 0;
	while ( std::string::npos != (i = base->find(find, i)) )
	{
		base->replace( i, lenfind, repl);
		i += lenrepl;
	}
}


void CGUIMcaLang::setBaseLanguage()
{
	int systemLanguage = configGetLanguage();
	if (systemLanguage == 1){
			CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
			CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Select slot"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "PS2 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "PS1 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Format"),
			CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Unformat"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "Create MC image"),
			CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "Restore MC image"),
			CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Memory Card Info"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Fast"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Full"),
			CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nSelect your memory card size"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MB"),
			CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Yes"),
			CGUIMcaLang::langmapRaw("LNG_OPER_NO", "No"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "Are you sure you want to format the memory card?\n\nFormatting will destroy all the data stored on the card!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "Are you sure you want to unformat the memory card?\n\nUnormatting will destroy all the data stored on the card!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "Are you sure you want to restore the memory card image?\n\nRestoring the image will destroy all the data stored on the card!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "Selected file already exists! Are you sure you want to overwrite it?\n\nOverwriting will cause all the file contents to be lost."),
			CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Warning..."),
			CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "Memory card in slot {SLOTNUM} has been pulled out or changed. Program will exit to main menu.\n\n\nPress X to continue."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nDo not remove the memory card, reset or switch off the console"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nOperation completed successfully\nPress X to continue"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nOperation has failed\nPress X to continue"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Select a file to read"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Select a file to write"),
			CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Memory Card Info"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "kB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
			CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Memory card slot:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Card type:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Page size:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Pages per block:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Total pages:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nSony for the console that has entertained us during long evenings, that has kept us awake during countless nights and which made our girlfriends to break up with us ;).\n\nPiotrB for taking a shot of his PS1 memory card and everyone else that has been involved in the PS1 MC photo session."),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "We'd like to thank:"),
			CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "START - create new file\nL2/R2 - enable/disable file mask"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "File mask enabled"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "File mask disabled"),
			CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "The specified filename contains invalid characters. Change the filename to continue.\n\n\nPress any button to continue."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nSelect a file to execute..."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nThe selected file is not a valid ELF executable."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nThe selected file couldn't be opened."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "You've selected a size bigger than default. This could damage the memory card!\n\nDo you want to continue?"),
		};
	} else if (systemLanguage == 2){
			CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
			CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Choisissez un port"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "Carte Mémoire PS2"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "Carte Mémoire PS1"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Formater"),
			CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Déformater"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "Créer une image de CM"),
			CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "Restaurer une image de CM"),
			CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Info sur la Carte Mémoire"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Rapide"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Complet"),
			CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nChoisissez la taille de votre Carte Mémoire"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MO"),
			CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Oui"),
			CGUIMcaLang::langmapRaw("LNG_OPER_NO", "Non"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "Êtes-vous certain(e) de vouloir formater la Carte Mémoire?\n\nLe formatage détruira toutes les données stockées sur la carte!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "Êtes vous certain(e) de vouloir déformater la Carte Mémoire?\n\nLe déformatage détruira toutes les données stockées sur la carte!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "Êtes vous certain(e) de vouloir restaurer l'image de Carte Mémoire?\n\nLa restauration de l'image détruira toutes les données stockées sur la carte!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "Le fichier choisi existe déjà! Êtes vous certain(e) de vouloir l'écraser?\n\nL'écrasement entrainera la perte du contenu du fichier."),
			CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Attention..."),
			CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "La Carte Mémoire dans le port {SLOTNUM} a été retirée ou remplacée. Le programme va revenir au menu principal.\n\n\nAppuyez sur X pour continuer."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nNe pas retirer la Carte Mémoire, redémarrer ou éteindre la console"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nOpération réussie\nAppuyer sur X pour continuer"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nÉchec de l'opération\nAppuyer sur X pour continuer"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Sélectionnez le fichier à ouvrir"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Sélectionnez le fichier de destination"),
			CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Infos Carte Mémoire"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MO"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "KO"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
			CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Port de Carte Mémoire"),
			CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Type de carte:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Taille de la page:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Pages par bloc:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Nombre de pages total:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nSony pour la console qui nous a distraits pendant de longues soirées, qui nous a gardés éveillés pendant de nombreuses nuit et qui a fait nos copines nous quitter ;).\n\nPiotrB pour avoir pris une photo de sa Carte Mémoire PS1 et tous ceux qui ont été impliqué dans le shooting de la MC PS1."),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "Nous voudrions remercier:"),
			CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "START - créer un nouveau fichier\nL2/R2 - activer/désactiver le masque de fichier"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "Masque de fichier activé"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "Masque de fichier désactivé"),
			CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "Le nom de fichier renseigné contient des caractères invalides. Changez le nom du fichier pour continuer.\n\n\nAppuyer sur n'importe quel bouton pour continuer."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nSélectionnez un fichier à exécuter..."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nLe fichier sélectionné n'est pas un exécutable ELF valide."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nLe fichier sélectionné n'a pas pu être ouvert."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "Vous avez sélectionné une taille supérieure à l'original. Ceci pourrait endommager la Carte Mémoire.\n\nVoulez-vous continuer?"),
		};
	} else if (systemLanguage == 3){
			CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
			CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Seleccionar ranura"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "Memory Card de PS2"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "Memory Card de PS1"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Formatear"),
			CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Deformatear"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "Crear imagen MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "Restaurar imagen MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Información MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Rápido"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Completo"),
			CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nSelecciona el tamaño de tu memory card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MB"),
			CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Sí"),
			CGUIMcaLang::langmapRaw("LNG_OPER_NO", "No"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "¿Seguro que deseas formatear la memory card?\n\n¡Formatear eliminará todos los datos almacenados en la tarjeta!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "¿Seguro que deseas dejar sin formato la memory card?\n\n¡Dejarla sin formato eliminará todos los datos almacenados en la tarjeta!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "¿Seguro que deseas restaurar la imagen de memory card?\n\n¡Restaurar la imagen eliminará todos los datos almacenados en la tarjeta!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "¡El archivo seleccionado ya existe! ¿Seguro que deseas sobrescribirlo?\n\nAl sobrescribir se perderá todo el contenido del archivo."),
			CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Peligro..."),
			CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "La Memory card de la ranura {SLOTNUM} ha sido extraída o cambiada. La aplicación volverá al menú principal.\n\n\nPulsa X para continuar."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nNo extraigas la memory card, reinicies o apagues la consola"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nOperación completada con éxito\nPulsa X para continuar"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nOperación fallida\nPulsa X para continuar"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Selecciona archivo para cargar"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Selecciona archivo para guardar"),
			CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Información MC"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "KB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
			CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Ranura de Memory card"),
			CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Tipo de tarjeta:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Tamaño de página:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Páginas por bloque:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Total de páginas:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nSony, por la consola que nos ha divertido durante largas veladas, que nos ha mantenido despiertos durante tantas noches e hicieron que nuestras novias rompieran con nosotros ;).\n\nPiotrB, por tomar una foto de su memory card de PS1 y a todos los demás que han participado en la sesión de fotos de la MC de PS1."),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "Agradecimientos para:"),
			CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "START - crear nuevo archivo\nL2/R2 - act/desac máscara de archivos"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "Máscara de archivos activada"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "Máscara de archivos desactivada"),
			CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "El nombre de archivo especificado contiene carácteres inválidos. Cambia el nombre de archivo para continuar.\n\n\nPulsa cualquier botón para continuar."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nSelecciona un archivo para ejecutar..."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nEl archivo seleccionado no es un ELF válido."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nEl archivo seleccionado no se puede abrir."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "El tamaño es distinto al por defecto. ¡Esto puede dañar la Memory Card!\n\n¿Seguro que desea continuar?"),
		};
	} else if (systemLanguage == 4){
			CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
			CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Slot wählen"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "PS2 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "PS1 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Formatieren"),
			CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Unformatieren"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "MC-Abbild erstellen"),
			CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "MC-Abbild wiederherstellen"),
			CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Memory Card Info"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Schnell"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Vollständig"),
			CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nWähle die Größe deiner Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MB"),
			CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Ja"),
			CGUIMcaLang::langmapRaw("LNG_OPER_NO", "Nein"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "Sicher, dass die Memory Card formatiert werden soll?\n\nDurch die Formatierung werden alle Daten gelöscht!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "Sicher, dass die Memory Card unformatiert werden soll?\n\nDurch die Unformatierung werden alle Daten gelöscht!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "Sicher, dass dieses Abbild wiederherstellt werden soll?\n\nDadurch gehen alle aktuellen Daten auf der Karte verloren."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "Die gewählte Datei existiert bereits! Sind Sie sicher, dass diese überschrieben werden soll?\n\nDadurch geht der aktuelle Inhalt verloren."),
			CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Warnung..."),
			CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "Die Memory Card in Slot {SLOTNUM} wurde entfernt oder getauscht. Das Programm wird jetzt zum Hauptmenü zurückkehren.\n\n\nDrücke X um fortzufahren."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nBitte die Memory Card nicht entfernen und die Konsole nicht ausschalten oder zurücksetzen."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nVorgang erfolgreich abgeschlossen.\nDrücke X um fortzufahren."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nVorgang fehlgeschlagen!\nDrücke X um fortzufahren."),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Quelldatei auswählen"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Zieldatei auswählen"),
			CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Memory Card Info"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "KB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
			CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Memory Card Slot"),
			CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Kartentyp:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Seiten-Größe:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Seiten pro Block:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Seiten-Anzahl:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nSony für eine Konsole, welche uns an langen Abenden unterhalten hat, zahllose Nächte durchmachen lies und unsere Freundinnen dazu brachte, Schluss zu machen ;)\n\nPiotrB für ein Foto seiner PS1-Memory-Card und alle anderen, welche bei der PS1 Memory Card Foto-Session mitgemacht haben."),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "User Dank geht an:"),
			CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "START - Neue Datei anlegen\nL2/R2 - Dateimaske ein/aus"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "Dateimaske aktiviert"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "Dateimaske deaktiviert"),
			CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "Der angegebene Dateiname enthält ungültige Zeichen und muss geändert werden um fortzufahren.\n\n\nDrücke eine beliebige Taste um fortzufahren."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nZu startenden Datei auswählen"),
			CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nDie gewählte Datei ist keine gültige ausführbare ELF-Datei."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nDie gewählte Datei konnte nicht geöffnet werden."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "Die ausgewählte Größe entspricht nicht der erkannten Größe der MemoryCard.\nDies könnte die MemoryCard beschädigen!\n\nMöchten Sie den Vorgang fortsetzen?"),
		};
	} else if (systemLanguage == 5){
			CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
			CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Seleziona slot"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "Memory Card PS2"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "Memory Card PS1"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Formatta"),
			CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Deformatta"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "Crea immagine MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "Ripristina immagine MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Info Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Veloce"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Completa"),
			CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nSeleziona la dimensione della MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MB"),
			CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Si"),
			CGUIMcaLang::langmapRaw("LNG_OPER_NO", "No"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "Sei sicuro/a di voler procedere con la formattazione?\n\nTutti i dati sulla Memory Card andranno persi!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "Sei sicuro/a di voler procedere con la formattazione?\n\nTutti i dati sulla Memory Card andranno persi!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "Sei sicuro/a di voler ripristinare l'immagine?\n\nTutti i dati sulla Memory Card andranno persi!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "Il file specificato esiste già, vuoi sovrascriverlo?\n\nI dati precedenti nel file andranno sovrascritti!."),),
			CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Attenzione..."),
			CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "La Memory card {SLOTNUM} è stata disinserita ed il programma tornerà alla schermata principale.\n\n\nPremi X per continuare"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nDNon rimuovere la Memory Card, resettare o spegnere la console"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nOperazione completata con successo!\nPremi X per continuare"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nOperation has failed\nPremi X per continuare"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Seleziona il file da leggere"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Seleziona il file da scrivere"),
			CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Memory Card Info"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "KB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
			CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Slot Memory card"),
			CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Tipologia:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Dimensione pagina:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Pagine per blocco:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Pagine totali:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nSony per la console che ci ha trattenuti durante la sera, tenendoci svegli e lontani dai nostri partner ;).\n\nPiotrB per la foto della sua Memory Card PS1 e per tutti i coinvolti per la foto di gruppo delle MC PS1."),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "Vorremmo ringraziare:"),
			CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "START - crea nuovo file\nL2/R2 - abilita/disabilita filtro file"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "Filtro file abilitato"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "Filtro file disabilitato"),
			CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "Il nome del file specificato contiene caratteri non validi. Per favore usa un nome differente.\n\n\nPremi un bottone per continuare"),
			CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nSeziona un file da eseguire..."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nIl file selezionato non è un valido ELF eseguibile."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nIl file selezionato non può essere aperto."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "Hai selezionato una dimensione troppo grande. Questo potrebbe danneggare la Memory Card!\n\nSei sicuro di voler continuare?"),
		};
	} else if (systemLanguage == 7){
			CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
			CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Selecionar entrada"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "PS2 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "PS1 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Formatar"),
			CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Desformatar"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "Criar copia MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "Restaurar copia MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Informacoes do MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Rapido"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Completo"),
			CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nSelecione o tamanho do MC"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MB"),
			CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Sim"),
			CGUIMcaLang::langmapRaw("LNG_OPER_NO", "Nao"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "Voce tem certeza que deseja formatar?\n\nFormatar ira destruir todos os dados do MC!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "Voce tem certeza que deseja desformatar?\n\nDesformatar ira destruir todos os dados do MC!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "Voce tem certeza que deseja restaurar a copia?\n\nRestaurar ira destruir todos os dados do MC!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "O arquivo selecionado jรก existe! Deseja sobescrever?\n\nSobescrever fara o arquivo original ser perdido."),
			CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Aviso..."),
			CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "Memory card no slot {SLOTNUM} foi removido ou substituido. O programa retornara para o menu principal.\n\n\nPressione X para continuar."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nNao remova o Memory Card ou resete o console."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nOperacao concluida com sucesso\nPressione X para continuar"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nA operacao falhou\nPressione X para continuar"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Selecione o arquivo para leitura"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Selecione o arquivo para gravacao"),
			CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Informacaoes do MC"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "kB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
			CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Memory card entrada:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Tipo de cartao:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Tamanho da pagina:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Paginas por bloco:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Total de paginas:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nSony pelo console que nos entreteu durante longas tardes, que nos manteve agordados durante incontaveis noites e que fez nossas namoradas terminarem conosco ;).\n\nPiotrB por tirar algumas fotos do seu memory card de PS1 e todos aqueles que se envolveram na sessao de fotos do MC de PS1."),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "Gostariamos de agradecer:"),
			CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "Inicio - Criar novo arquivo\nL2/R2 - ativar/desativar mascara de arquivo"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "Mascara de arquivo ativada"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "Mascara de arquivo desativada"),
			CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "O nome de arquivo especificado contem caracteres invalidos. Altere o nome para continuar.\n\n\nPressione qualquer botao para continuar."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nSelecione um arquivo para executar..."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nO arquivo selecionado nao e um ELF executavel."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nO arquivo selecionado nao pode ser aberto."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "Voce selecionou um tamanho maior que o padrao. Isso pode danificar seu memorycard!\n\nVoce quer continuar?"),
		};
	} else {
			CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
			CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Select slot"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "PS2 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "PS1 Memory Card"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Format"),
			CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Unformat"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "Create MC image"),
			CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "Restore MC image"),
			CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Memory Card Info"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Fast"),
			CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Full"),
			CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nSelect your memory card size"),
			CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MB"),
			CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Yes"),
			CGUIMcaLang::langmapRaw("LNG_OPER_NO", "No"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "Are you sure you want to format the memory card?\n\nFormatting will destroy all the data stored on the card!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "Are you sure you want to unformat the memory card?\n\nUnormatting will destroy all the data stored on the card!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "Are you sure you want to restore the memory card image?\n\nRestoring the image will destroy all the data stored on the card!"),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "Selected file already exists! Are you sure you want to overwrite it?\n\nOverwriting will cause all the file contents to be lost."),
			CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Warning..."),
			CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "Memory card in slot {SLOTNUM} has been pulled out or changed. Program will exit to main menu.\n\n\nPress X to continue."),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nDo not remove the memory card, reset or switch off the console"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nOperation completed successfully\nPress X to continue"),
			CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nOperation has failed\nPress X to continue"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Select a file to read"),
			CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Select a file to write"),
			CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Memory Card Info"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "kB"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
			CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
			CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Memory card slot:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Card type:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Page size:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Pages per block:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Total pages:"),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nSony for the console that has entertained us during long evenings, that has kept us awake during countless nights and which made our girlfriends to break up with us ;).\n\nPiotrB for taking a shot of his PS1 memory card and everyone else that has been involved in the PS1 MC photo session."),
			CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "We'd like to thank:"),
			CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "START - create new file\nL2/R2 - enable/disable file mask"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "File mask enabled"),
			CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "File mask disabled"),
			CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "The specified filename contains invalid characters. Change the filename to continue.\n\n\nPress any button to continue."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nSelect a file to execute..."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nThe selected file is not a valid ELF executable."),
			CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nThe selected file couldn't be opened."),
			CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "You've selected a size bigger than default. This could damage the memory card!\n\nDo you want to continue?"),
		};
	}
}

CGUIMcaLang::setBaseLanguage()

const int CGUIMcaLang::m_numof_entries = sizeof(CGUIMcaLang::m_default_lang_raw) / sizeof CGUIMcaLang::m_default_lang_raw[0];
const std::map<const std::string, const std::string> CGUIMcaLang::m_default_lang(CGUIMcaLang::m_default_lang_raw, CGUIMcaLang::m_default_lang_raw + CGUIMcaLang::m_numof_entries);
