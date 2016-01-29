module Paths_gtk2hs_buildtools (
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
version = Version {versionBranch = [0,13,0,5], versionTags = []}
bindir, libdir, datadir, libexecdir :: FilePath

bindir     = "/home/kazek/.cabal/bin"
libdir     = "/home/kazek/.cabal/lib/gtk2hs-buildtools-0.13.0.5/ghc-7.6.3"
datadir    = "/home/kazek/.cabal/share/gtk2hs-buildtools-0.13.0.5"
libexecdir = "/home/kazek/.cabal/libexec"

getBinDir, getLibDir, getDataDir, getLibexecDir :: IO FilePath
getBinDir = catchIO (getEnv "gtk2hs_buildtools_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "gtk2hs_buildtools_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "gtk2hs_buildtools_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "gtk2hs_buildtools_libexecdir") (\_ -> return libexecdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
