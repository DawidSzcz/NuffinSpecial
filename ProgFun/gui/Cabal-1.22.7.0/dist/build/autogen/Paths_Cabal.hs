module Paths_Cabal (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch


version :: Version
version = Version {versionBranch = [1,22,7,0], versionTags = []}
bindir, libdir, datadir, libexecdir :: FilePath

bindir     = "/home/kazek/.cabal/bin"
libdir     = "/home/kazek/.cabal/lib/Cabal-1.22.7.0/ghc-7.6.3"
datadir    = "/home/kazek/.cabal/share/Cabal-1.22.7.0"
libexecdir = "/home/kazek/.cabal/libexec"

getBinDir, getLibDir, getDataDir, getLibexecDir :: IO FilePath
getBinDir = catchIO (getEnv "Cabal_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "Cabal_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "Cabal_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "Cabal_libexecdir") (\_ -> return libexecdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
