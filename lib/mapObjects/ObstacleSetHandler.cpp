/*
 * ObstacleSetHandler.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "ObstacleSetHandler.h"

#include "../modding/IdentifierStorage.h"
#include "../constants/StringConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

ObstacleSet::ObstacleSet():
	type(INVALID),
	allowedTerrains({TerrainId::NONE})
{
}

ObstacleSet::ObstacleSet(EObstacleType type, TerrainId terrain):
	type(type),
	allowedTerrains({terrain})
{
}

void ObstacleSet::addObstacle(std::shared_ptr<const ObjectTemplate> obstacle)
{
	obstacles.push_back(obstacle);
}

ObstacleSetFilter::ObstacleSetFilter(std::vector<ObstacleSet::EObstacleType> allowedTypes, TerrainId terrain = TerrainId::ANY_TERRAIN, EAlignment alignment = EAlignment::ANY):
	allowedTypes(allowedTypes),
	terrain(terrain),
	alignment(alignment)
{
}

ObstacleSetFilter::ObstacleSetFilter(ObstacleSet::EObstacleType allowedType, TerrainId terrain = TerrainId::ANY_TERRAIN, EAlignment alignment = EAlignment::ANY):
	allowedTypes({allowedType}),
	terrain(terrain),
	alignment(alignment)
{
}

bool ObstacleSetFilter::filter(const ObstacleSet &set) const
{
	if (terrain != TerrainId::ANY_TERRAIN && !vstd::contains(set.getTerrains(), terrain))
	{
		return false;
	}

	// TODO: Also check specific factions
	if (alignment != EAlignment::ANY)
	{
		auto alignments = set.getAlignments();
		if (!alignments.empty() && !vstd::contains(alignments, alignment))
		{
			return false;
		}
	}

	return true;
}

TerrainId ObstacleSetFilter::getTerrain() const
{
	return terrain;
}

std::set<TerrainId> ObstacleSet::getTerrains() const
{
	return allowedTerrains;
}

void ObstacleSet::setTerrain(TerrainId terrain)
{
	this->allowedTerrains = {terrain};
}

void ObstacleSet::setTerrains(const std::set<TerrainId> & terrains)
{
	this->allowedTerrains = terrains;
}

void ObstacleSet::addTerrain(TerrainId terrain)
{
	this->allowedTerrains.insert(terrain);
}

void ObstacleSet::addAlignment(EAlignment alignment)
{
	this->allowedAlignments.insert(alignment);
}

std::set<EAlignment> ObstacleSet::getAlignments() const
{
	return allowedAlignments;
}

ObstacleSet::EObstacleType ObstacleSet::getType() const
{
	return type;
}

void ObstacleSet::setType(EObstacleType type)
{
	this->type = type;
}

std::vector<std::shared_ptr<const ObjectTemplate>> ObstacleSet::getObstacles() const
{
	return obstacles;
}

ObstacleSet::EObstacleType ObstacleSetHandler::convertObstacleClass(MapObjectID id)
{
	switch (id)
	{
		case Obj::MOUNTAIN:
		case Obj::VOLCANIC_VENT:
		case Obj::VOLCANO:
		case Obj::REEF:
			return ObstacleSet::MOUNTAINS;
		case Obj::OAK_TREES:
		case Obj::PINE_TREES:
		case Obj::TREES:
		case Obj::DEAD_VEGETATION:
		case Obj::HEDGE:
		case Obj::KELP:
		case Obj::WILLOW_TREES:
		case Obj::YUCCA_TREES:
			return ObstacleSet::TREES;
		case Obj::FROZEN_LAKE:
		case Obj::LAKE:
		case Obj::LAVA_FLOW:
		case Obj::LAVA_LAKE:
			return ObstacleSet::LAKES;
		case Obj::CANYON:
		case Obj::CRATER:
		case Obj::SAND_PIT:
		case Obj::TAR_PIT:
			return ObstacleSet::CRATERS;
		case Obj::HILL:
		case Obj::MOUND:
		case Obj::OUTCROPPING:
		case Obj::ROCK:
		case Obj::SAND_DUNE:
		case Obj::STALAGMITE:
			return ObstacleSet::ROCKS;
		case Obj::BUSH:
		case Obj::CACTUS:
		case Obj::FLOWERS:
		case Obj::MUSHROOMS:
		case Obj::LOG:
		case Obj::MANDRAKE:
		case Obj::MOSS:
		case Obj::PLANT:
		case Obj::SHRUB:
		case Obj::STUMP:
		case Obj::VINE:
			return ObstacleSet::PLANTS;
		case Obj::SKULL:
			return ObstacleSet::ANIMALS;
		default:
			return ObstacleSet::OTHER;
	}
}

ObstacleSet::EObstacleType ObstacleSet::typeFromString(const std::string &str)
{
	static const std::map<std::string, EObstacleType> OBSTACLE_TYPE_NAMES =
	{
		{"mountain", MOUNTAINS},
		{"tree", TREES},
		{"lake", LAKES},
		{"crater", CRATERS},
		{"rock", ROCKS},
		{"plant", PLANTS},
		{"structure", STRUCTURES},
		{"animal", ANIMALS},
		{"other", OTHER}
	};

	if (OBSTACLE_TYPE_NAMES.find(str) != OBSTACLE_TYPE_NAMES.end())
	{
		return OBSTACLE_TYPE_NAMES.at(str);
	}

	// TODO: How to handle that?
	throw std::runtime_error("Invalid obstacle type: " + str);
}

std::string ObstacleSet::toString() const
{
	static const std::map<EObstacleType, std::string> OBSTACLE_TYPE_STRINGS =
	{
		{MOUNTAINS, "mountain"},
		{TREES, "tree"},
		{LAKES, "lake"},
		{CRATERS, "crater"},
		{ROCKS, "rock"},
		{PLANTS, "plant"},
		{STRUCTURES, "structure"},
		{ANIMALS, "animal"},
		{OTHER, "other"}
	};

	return OBSTACLE_TYPE_STRINGS.at(type);
}

std::vector<ObstacleSet::EObstacleType> ObstacleSetFilter::getAllowedTypes() const
{
	return allowedTypes;
}

void ObstacleSetFilter::setType(ObstacleSet::EObstacleType type)
{
	allowedTypes = {type};
}

void ObstacleSetFilter::setTypes(std::vector<ObstacleSet::EObstacleType> types)
{
	this->allowedTypes = types;
}

std::vector<JsonNode> ObstacleSetHandler::loadLegacyData()
{
	return {};
}

void ObstacleSetHandler::loadObject(std::string scope, std::string name, const JsonNode & data)
{
	auto os = loadFromJson(scope, data, name, biomes.size());
	if(os)
	{
		addObstacleSet(os);
		// TODO: Define some const array of object types ("biome" etc.)
		VLC->identifiersHandler->registerObject(scope, "biome", name, biomes.back()->id);
	}
	else
	{
		logMod->error("Failed to load obstacle set: %s", name);
	}
}

void ObstacleSetHandler::loadObject(std::string scope, std::string name, const JsonNode & data, size_t index)
{
	auto os = loadFromJson(scope, data, name, index);
	if(os)
	{
		addObstacleSet(os);
		VLC->identifiersHandler->registerObject(scope, "biome", name, biomes.at(index)->id);
	}
	else
	{
		logMod->error("Failed to load obstacle set: %s", name);
	}

}

std::shared_ptr<ObstacleSet> ObstacleSetHandler::loadFromJson(const std::string & scope, const JsonNode & json, const std::string & name, size_t index)
{
	auto os = std::make_shared<ObstacleSet>();
	os->id = index;

	auto biome = json["biome"].Struct();
	os->setType(ObstacleSet::typeFromString(biome["objectType"].String()));

	// TODO: Handle any (every) terrain option

	if (biome["terrain"].isString())
	{
		auto terrainName = biome["terrain"].String();

		VLC->identifiers()->requestIdentifier(scope, "terrain", terrainName, [os](si32 id)
		{
			os->setTerrain(TerrainId(id));
		});
	}
	else // Other cases won't pass validation
	{
		auto terrains = biome["terrain"].Vector();

		for (const auto & terrain : terrains)
		{
			VLC->identifiers()->requestIdentifier(scope, "terrain", terrain.String(), [os](si32 id)
			{
				os->addTerrain(TerrainId(id));
			});
		}
	}

	// TODO: Move this parser to some utils
	auto parseAlignment = [](const std::string & str) ->EAlignment
	{
		int alignment = vstd::find_pos(GameConstants::ALIGNMENT_NAMES, str);
		if (alignment == -1)
		{
			logGlobal->error("Incorrect alignment: ", str);
			return EAlignment::ANY;
		}
		else
		{
			return static_cast<EAlignment>(alignment);
		}
	};

	if (biome["alignment"].isString())
	{
		os->addAlignment(parseAlignment(biome["alignment"].String()));
	}
	else if (biome["alignment"].isVector())
	{
		auto alignments = biome["alignment"].Vector();
		for (const auto & node : alignments)
		{
			os->addAlignment(parseAlignment(node.String()));
		}
	}

	auto templates = json["templates"].Vector();
	for (const auto & node : templates)
	{
		logGlobal->info("Registering obstacle template: %s in scope %s", node.String(), scope);

		auto identifier = boost::algorithm::to_lower_copy(node.String());
		auto jsonName = JsonNode(identifier);

		VLC->identifiers()->requestIdentifier(node.getModScope(), "obstacleTemplate", identifier, [this, os](si32 id)
		{
			logGlobal->info("Resolved obstacle id: %d", id);
			os->addObstacle(obstacleTemplates[id]);
		});
	}

	return os;
}

void ObstacleSetHandler::addTemplate(const std::string & scope, const std::string &name, std::shared_ptr<const ObjectTemplate> tmpl)
{
	auto id = obstacleTemplates.size();

	auto strippedName = boost::algorithm::to_lower_copy(name);
	auto pos = strippedName.find(".def");
	if(pos != std::string::npos)
		strippedName.erase(pos, 4);

	if (VLC->identifiersHandler->getIdentifier(scope, "obstacleTemplate", strippedName, true))
	{
		logMod->warn("Duplicate obstacle template: %s", strippedName);
		return;
	}
	else
	{
		// Save by name
		VLC->identifiersHandler->registerObject(scope, "obstacleTemplate", strippedName, id);

		// Index by id
		obstacleTemplates[id] = tmpl;
	}
}

void ObstacleSetHandler::addObstacleSet(std::shared_ptr<ObstacleSet> os)
{
	obstacleSets[os->getType()].push_back(os);
	biomes.push_back(os);
}

TObstacleTypes ObstacleSetHandler::getObstacles( const ObstacleSetFilter &filter) const
{
	TObstacleTypes result;

	for (const auto &allowedType : filter.getAllowedTypes())
	{
		auto it = obstacleSets.find(allowedType);
		if(it != obstacleSets.end())
		{
			for (const auto &os : it->second)
			{
				if (filter.filter(*os))
				{
					result.push_back(os);
				}
			}
		}
	}
	return result;
}

VCMI_LIB_NAMESPACE_END

